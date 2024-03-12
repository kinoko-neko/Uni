fn print(n: i32) -> Option<String> {
    if n < 1 || n%2 == 0 {
        return None
    }
    //     *(1 +2i)
    let mut ret = String::new();
    let mut pom;
    for i in 0..n {
        pom = i;
        if i > n/2 {
            pom = n - i -1;
        }
        pom = 1 + pom*2;
        ret.push_str(&" ".repeat(((n-pom)/2) as usize));
        ret.push_str(&"*".repeat(pom as usize));
        //ret.push_str(&" ".repeat(((n-pom)/2) as usize));
        ret.push_str("\n");
    }
    Some(ret)
}

fn main() {
    println!("Hello, world!");
    println!("{}",print(3i32).unwrap());
}

#[test]
fn t0() {
  assert_eq!(print(3), Some(" *\n***\n *\n".to_string()) );
}
#[test]
fn t1() {
  assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()) );
}
#[test]
fn t2() {
  assert_eq!(print(-3),None);
}
#[test]
fn t3() {
  assert_eq!(print(2),None);
}
#[test]
fn t4() {
  assert_eq!(print(0),None);
}
#[test]
fn t5() {
  assert_eq!(print(1), Some("*\n".to_string()) );
}
