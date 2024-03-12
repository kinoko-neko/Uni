fn reverse_words(str: &str) -> String {
    // your code here
    str.split(' ').map(|x| x.chars().rev().collect::<String>()).collect::<Vec<String> >().join(" ")
  //  "Test String".to_string()
}

fn main() {
    println!("Hello, world!");
}

// Rust tests

#[test]
fn t1() {
  assert_eq!(reverse_words("The quick brown fox jumps over the lazy dog."), "ehT kciuq nworb xof spmuj revo eht yzal .god");
}
#[test]
fn t2() {
  assert_eq!(reverse_words("apple"), "elppa");
}
#[test]
fn t3() {
  assert_eq!(reverse_words("a b c d"),"a b c d");
  }
#[test]
fn t4() {
  assert_eq!(reverse_words("double  spaced  words kajak"), "elbuod  decaps  sdrow kajak");
}
#[test]
fn t5() {
  assert_eq!(reverse_words("soup soup"), "puos puos");
}
