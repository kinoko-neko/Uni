enum Typ{
    Left,
    Right,
    Forward,
}

pub fn execute(code: &str) -> String {
  // Implement your RS1 interpreter he

    if code == "" {return "*".to_string();}

    let mut ops:Vec<(Typ,Option<usize>)> = vec![];
    for x in code.chars(){
        match x{
            'F' => ops.push((Typ::Forward,None)),
            'L' => ops.push((Typ::Left,None)),
            'R'=> ops.push((Typ::Right,None)),
            '0'..='9'=> {
                let ls = ops.last_mut().unwrap();
                let num = x.to_digit(10).unwrap() as usize;
                match ls.1 {
                    Some(k) => ls.1 = Some(10*k + num),
                    _ => ls.1 = Some(num),
                }
            },
            _ => ()
        }
    }
 //   println!("for1 done");
    let mut ar = [1,1,1,1];
    let moves = [(0i64,1i64),(1,0),(0,-1),(-1,0)];
    let mut dir = 1;
    let mut pos:Vec<(i64,i64)> = vec![];
    let mut akt = (1,1);
    pos.push(akt);
    for x in ops {
        let n =  x.1.unwrap_or(1);
        match x.0 {
            Typ::Left => dir = (dir + n%4)%4,
            Typ::Right => dir = (dir + (n*3)%4)%4, // 3 = -1 w mod 4
            Typ::Forward => {
                for _i in 0..n{
                    akt = ((moves[dir].0)+akt.0,(moves[dir].1)+akt.1);
                    pos.push(akt);
                }

            },
        }
   //     println!("({},{}) {}",akt.0,akt.1,dir);
        ar[0] = std::cmp::max(ar[0],akt.1);
        ar[1] = std::cmp::max(ar[1],akt.0);
        ar[2] = std::cmp::min(ar[2],akt.1);
        ar[3] = std::cmp::min(ar[3],akt.0);
 //       println!("e");

    }
    println!("for2 done {} {} {} {}",ar[0],ar[1],ar[2],ar[3]);
    let x = ar[1]+1-ar[3];
    let y = ar[0]+1-ar[2];
    let mut grid:Vec<Vec<char> > = vec![vec![' ';x as usize];y as usize];
    let xad= -ar[3];
    let yad= -ar[2];
  //  println!("{} {} {} {}",x,y,xad,yad);
    for p in pos{
        grid[(yad+p.1) as usize][(xad+p.0) as usize]='*';
    }
  //  println!("for3 done");
    grid.iter().map(|x| x.iter().collect::<String>()).collect::<Vec<String>>().join("\r\n")
    //"".to_string()
}

fn main() {
    println!("{}",execute("LF5RF3RF3RF7"));

    println!("Hello, world!");
}

#[cfg(test)]
macro_rules! expect_equal {
  ($actual:expr, $expected:expr $(,)*) => {{
    let actual = $actual;
    let expected = $expected;
    assert_eq!(actual, expected, "\ngot:\n{}\n\nexpected:\n{}\n", actual, expected);
  }};
}

#[cfg(test)]
mod tests {
use super::execute;


#[test]
fn t1() {
  expect_equal!(execute(""), "*");
}
#[test]
fn t2() {
  expect_equal!(execute("FFFFF"), "******");
}
#[test]
fn t3() {
  expect_equal!(
    execute("FFFFFLFFFFFLFFFFFLFFFFFL"),
    "******\r\n*    *\r\n*    *\r\n*    *\r\n*    *\r\n******",
  );
}
#[test]
fn t4() {
  expect_equal!(
    execute("LFFFFFRFFFRFFFRFFFFFFF"),
    "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
  );
}
#[test]
fn t5() {
  expect_equal!(
    execute("LF5RF3RF3RF7"),
    "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
  );

}
}

