fn last_digit(str1: &str, str2: &str) -> i32 {
 //   let phi = vec!(1,1,2,2,4,2,6,4,6);
    let n:i32 = str1.split_at(str1.len()-1).1.parse().unwrap();
    let m: i32 = match str2.len() {
        1 => str2.parse().unwrap(),
        _ => str2.split_at(str2.len()-2).1.parse().unwrap()
    };

    if m==0 && str2.len()==1{
        return 1;
    }
   let m2:i32 = n%2;
   let m5:i32 = (n%5).pow(((m%4)+4) as u32)%5;
   match m2 - (m5%2){
     0 => m5,
     _ => m5+5
    }
}

fn main() {
    println!("{}",last_digit("10","10000000000"));
}

#[test]
fn test1() {
  assert_eq!(last_digit("4", "1"), 4);
}
#[test]
fn test2() {
  assert_eq!(last_digit("4", "2"), 6);
}
#[test]
fn test3() {
  assert_eq!(last_digit("9", "7"), 9);
}
#[test]
fn test4() {
  assert_eq!(last_digit("10","10000000000"), 0);
}
#[test]
fn test5() {
    assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
}
#[test]
fn test6() {
  assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
}
#[test]
fn test7() {
  assert_eq!(last_digit("2", "2"), 4);
}
#[test]
fn test8() {
  assert_eq!(last_digit("2", "10"), 4);
}
#[test]
fn test9() {
  assert_eq!(last_digit("11", "678907"), 1);
}
#[test]
fn test10() {
  assert_eq!(last_digit("3456785", "09876543"), 5);
}
#[test]
fn test11() {
  assert_eq!(last_digit("4567890", "345678"), 0);
}
