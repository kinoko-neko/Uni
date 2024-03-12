use crate::parser::Exp::*;
use crate::parser::OP::*;
use std::collections::HashMap;

#[derive(Clone)]
pub enum Value {
    Num(i64),
    Str(String),
    List(Vec<String>),
    Void,
}

#[derive(Clone)]
pub enum OP {
    Sub,
    Mul,
    Div,
    Le,
}

#[derive(Clone)]
pub enum Exp {
    Call(String, Vec<Exp>), //wywołanie procedury
    Oper(OP, Box<Exp>, Box<Exp>), //operator
    Const(Value), //stala
    Var(String), //zmienna
}

fn make_value(tekst: &str) -> Option<Exp> {
    //specjalna zmienna
    if tekst == "repcount"  {
        return Some(Var("repcount".to_string()));
    }
    //normalne warotsci
    if let Some(name) = tekst.strip_prefix('"') {
        Some(Const(Value::Str(name.to_string())))
    }
    else if let Some(name) = tekst.strip_prefix(':') {
        Some(Var(name.to_string()))
    }
    else {
        match tekst.parse() {
            Ok(n) => Some(Const(Value::Num(n))),
            Err(_) => None,//nie jest zadna wartoscia
        }
    }
}
#[derive(Clone)]
pub struct Procedure {
    name: String,
    vars: Vec<String>,
    body: Vec<String>,
}

impl Procedure {
    pub fn name(&self) -> &str {
        &self.name
    }
    pub fn argc(&self) -> usize {
        self.vars.len()
    }
}

pub enum Stan {
    ProcDef(Procedure),
    Exp(Exp),
}

#[derive(Clone)]
enum ExpState {
    Empty,
    Val(Exp),
    Op(Exp, OP),
}

struct ExpParser {
    state: ExpState,
}


impl ExpParser {
    fn new() -> ExpParser {
        ExpParser {
            state: ExpState::Empty,
        }
    }

    fn can_take_val(&self) -> bool {
        use ExpState::*;
        match self.state {
            Empty | Op(_, _) => true,
            Val(_) => false,
        }
    }

    fn add_op(&mut self, op: OP) -> bool {
        use ExpState::*;
        match self.state.clone() {
            Val(v) => {
                self.state = Op(v, op);
                true
            }
            _ => false,
        }
    }

    fn add_val(&mut self, val: Exp) -> bool {
        use ExpState::*;
        match self.state.clone() {
            Empty => {
                self.state = Val(val);
                true
            }
            Op(v, op) => {
                self.state = Val(Oper(op, Box::new(v), Box::new(val)));
                true
            }
            _ => false,
        }
    }

    fn is_val(&mut self) -> bool {
        use ExpState::*;
        match  self.state.clone() {
            Val(_x) => true,
            _ => false
        }
    }

    fn ret_value(self) -> Exp {
        use ExpState::*;
        match self.state {
            Val(v) => v,
            Empty => panic!("empy No value!"),
            Op(_, _) => panic!("No second argument!"),
        }
    }
}

fn parse_exp(procs: &HashMap<String, usize>, iter: &Vec<&str>, wsk: &mut usize) -> Exp {
    let mut expparser = ExpParser::new();
    let mut wsk2 = *wsk;
    while wsk2 < iter.len() {
        *wsk += 1;
        match iter[wsk2.to_owned()] {
            "-" =>{
                expparser.add_op(Sub);
            }
            "*" =>{
                expparser.add_op(Mul);
            }
            "/" =>{
                expparser.add_op(Div);
            }
            "<" =>{
                expparser.add_op(Le);
            }
            //TODO nawias kwadratowy
            "[" => {
                if !expparser.can_take_val(){
                    *wsk -= 1;
                    return expparser.ret_value();
                }
                let mut list = vec![];
                let x;
                let mut ok = false;
                while *wsk< iter.len() {

                    match iter[*wsk] {
                        "]" => {
                            *wsk+= 1;
                            ok = true;
                            x = Const(Value::List(list));
                            expparser.add_val(x);

                            //println!("domknieto nawias");
                            if expparser.is_val(){
                              //  println!("val");
                                return expparser.ret_value();
                            }
                           // else{
                                //println!("no value");
                            //}

                            break;
                        },
                        _ => {list.push(iter[*wsk].to_string());
                            *wsk+= 1;
                        }

                    }

                };
                if !ok{
                    panic!("nie domkniety nawias");
                }

            }
            _ =>{
                if !expparser.can_take_val(){
                    *wsk-=1;
                    return expparser.ret_value();
                }
              //  println!("eeee {}",iter[wsk2.to_owned()]);
                //tu moze być wartość albo procedura
                match make_value(iter[wsk2.to_owned()]) {
                    Some(a) => {
                        if !expparser.add_val(a) {
                            *wsk-=1;
                            return expparser.ret_value();
                        }
                    }
                    None => {
                      //  println!("e2 {}",iter[wsk2.to_owned()]);
                        match procs.get(iter[wsk2.to_owned()]) {
                            Some(nargs) =>{
                                let args: Vec<&str>;

                                if *nargs == 0 {
                                    args = vec![];
                                }
                                else{
                                    args = iter[wsk2+1..=wsk2+*nargs].to_vec();
                                }
                                let nazwa = iter[wsk2.to_owned()].to_string();

                                let arg: Vec<Exp> = args.iter().map(|_| parse_exp(procs, iter, wsk)).collect();
                                expparser.add_val(Exp::Call(nazwa, arg));
                            }
                            None =>{
                                *wsk -= 1;
                                return expparser.ret_value();
                            }
                        }
                    }
                }

            }
        }
        wsk2 = *wsk;
    }
    expparser.ret_value()
}

fn parse_proc(iter: &Vec<&str>, wsk: &mut usize) -> Procedure {
    //name
    let nazwa: String;
    let mut args: Vec<String> = vec![];
    let mut cialo: Vec<String> = vec![];

    if *wsk < iter.len(){
        nazwa = iter[*wsk].to_owned();
    }
    else{
        panic!("no name");
    }
    *wsk += 1;
    //args
    while *wsk < iter.len(){
        match iter[*wsk].strip_prefix(":") {
            Some(arg) =>{
                *wsk += 1;
                args.push(arg.to_owned());
            }
            None =>{
                break;
            }
        }
    }
    //body

    while *wsk < iter.len(){
        match iter[*wsk] {
            "END" | "end" =>{
                *wsk +=1;
                break;
            }
            _ =>{
                *wsk += 1;
                cialo.push(iter[*wsk].to_owned());
            }
        }
    }
    //ret
    Procedure { name: nazwa, vars:args , body:cialo  }
}

pub fn parse_line(procs: &HashMap<String, usize>, iter:  &Vec<&str>, wsk: &mut usize) -> Option<Stan> {
    if wsk.to_owned() >= iter.len() {
        return None;
    }
    match iter[wsk.to_owned()] {
        "TO" | "to" => {
            //println!("parse proc");
            *wsk+=1;
            Some(Stan::ProcDef(parse_proc(iter, wsk)))
        }
        _ => Some(Stan::Exp(parse_exp(procs,iter, wsk)))
    }
}


