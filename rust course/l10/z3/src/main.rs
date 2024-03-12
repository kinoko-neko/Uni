fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    if a.len() != b.len(){
        return false;
    }

    let mut am: Vec<i64> = a.into_iter().map(|x| x.pow(2)).collect();
    let mut bm: Vec<i64> = b;
    am.sort();
    bm.sort();
    if am == bm {
        return true;
    }
    return false;
}

fn main() {
    println!("Hello, world!");
}

fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
    assert_eq!(comp(a, b), exp)
}

#[test]
fn t0() {

    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, true);
}
#[test]
fn t1() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, false);
}
#[test]
fn t2() {
    let a1 = vec![2, 2, 3];
    let a2 = vec![4, 9, 9];
    testing(a1, a2, false);
}
#[test]
fn t3() {
    testing(vec![103, 71, 24, 653, 52], vec![10609, 576, 426409, 5041, 2704], true);
}
#[test]
fn t4() {
    let a1 = vec![4, 4];
    let a2 = vec![1, 31];
    testing(a1, a2, false);
}
