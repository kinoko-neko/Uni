fn descending_order(x: u64) -> u64 {
    let mut v:Vec<u32> = x.to_string().chars().map(|x| x.to_digit(10).unwrap()).collect::<Vec<u32> >();
    v.sort();
    v.into_iter().rev().map(|x| x.to_string()).collect::<String>().parse::<u64>().unwrap()

  //  12u64
}

fn main() {
    println!("Hello, world!");
}

#[test]
fn t1() {
    assert_eq!(descending_order(0), 0);
}
#[test]
fn t2() {
    assert_eq!(descending_order(1), 1);
}
#[test]
fn t3() {
    assert_eq!(descending_order(15), 51);
}
#[test]
fn t4() {
    assert_eq!(descending_order(1021), 2110);
}
#[test]
fn t5() {
    assert_eq!(descending_order(123456789), 987654321);
}
#[test]
fn t6() {
    assert_eq!(descending_order(145263), 654321);
}
