use std::env;
use std::fs;
use std::collections::HashMap;
use crate::parser::*;

mod parser;

fn init_procs() -> HashMap<String, usize> {
    let mut procs: HashMap<String, usize> = HashMap::new();
    procs.insert("repeat".to_string(), 2);
    procs.insert("clearscreen".to_string(), 0);
    procs.insert("fd".to_string(), 1);
    procs.insert("forward".to_string(), 1);
    procs.insert("rt".to_string(), 1);
    procs.insert("right".to_string(), 1);
    procs.insert("bk".to_string(), 1);
    procs.insert("back".to_string(), 1);
    procs.insert("lt".to_string(), 1);
    procs.insert("left".to_string(), 1);
    procs.insert("setcolor".to_string(), 1);
    procs.insert("pick".to_string(), 1);
    procs.insert("random".to_string(), 1);
    procs.insert("window".to_string(), 0);
    procs.insert("hideturtle".to_string(), 0);
    procs.insert("setlabelheight".to_string(), 1);
    procs.insert("showturtle".to_string(), 0);
    procs.insert("if".to_string(), 2);
    procs.insert("penup".to_string(), 0);
    procs.insert("pendown".to_string(), 0);
    procs.insert("pu".to_string(), 0);
    procs.insert("pd".to_string(), 0);
    procs.insert("setturtle".to_string(), 1);
    procs.insert("wait".to_string(), 1);
    procs.insert("stop".to_string(), 0);
    procs.insert("label".to_string(), 1);
    procs.insert("wait".to_string(), 1);
    procs
}

fn stringval(v:Value) -> String{
    match v{
        Value::Num(n) => n.to_string(),
        Value::Str(s) => s,
        Value::List(l) => l.join(","),
        Value::Void => "void".to_owned(),
    }
}

fn stringexp(e:Exp) -> String {
    match e {
        Exp::Var(a) =>{
            format!("variable: {}",a)
            }
        Exp::Call(a,b) =>{
                let args = b.into_iter().map(stringexp).collect::<Vec<String>>().join(",");
                format!("wywolanie: {} argumenty:{}",a,args)
            }
        Exp::Const(a) =>{
                format!("stala: {}",stringval(a))
            }
        Exp::Oper(a,b ,c ) =>{
                match a{
                    OP::Sub => {
                           format!("{} - {}",stringexp(*b),stringexp(*c))
                        }
                    OP::Mul =>{
                            format!("{} * {}",stringexp(*b),stringexp(*c))
                        }
                    OP::Div =>{
                            format!("{} / {}",stringexp(*b),stringexp(*c))
                        }
                    OP::Le => {
                            format!("{} < {}",stringexp(*b),stringexp(*c))
                        }
                    }
                }
            }
}

fn it(procs: &mut HashMap<String, usize>, iter:  &Vec<&str>, wsk: &mut usize ) {
    loop {
        match parse_line(procs, iter, wsk) {
            Some(Stan::ProcDef(proc)) => {
                println!("procedura:{}",proc.name());
                procs.insert(proc.name().to_string(),proc.argc() );
            }
            Some(Stan::Exp(e)) => println!("{}",stringexp(e)),

            None => return (),
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let file_path = args[1].clone();

    let tekst = fs::read_to_string(file_path).expect("not read");

    let dane: Vec<&str> = tekst.split_whitespace().collect();
    println!("dane: {}\n",dane.join(" "));

    let mut procs = init_procs();
    let mut wsk: usize = 0;
    it(&mut procs, &dane, &mut wsk);

}
