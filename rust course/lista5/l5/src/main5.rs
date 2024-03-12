fn sum_pairs(ints: &[i8], s: i8) -> Option<(i8, i8)> {
    // your code
    let mut e= std::collections::HashSet::new();
    for i in 0..ints.len(){
        if e.contains(&(s-ints[i])) {
            return Some((s-ints[i],ints[i]));
        }
        else{
            e.insert(ints[i]);
        }
    }
    None
}

fn main() {
    println!("Hello, world!");
}

const l1: [i8;6] = [1i8, 4, 8, 7, 3, 15];
const l2: [i8;6] = [1i8, -2, 3, 0, -6, 1];
const l3: [i8;3] = [20i8, -13, 40];
const l4: [i8;6] = [1i8, 2, 3, 4, 1, 0];
const l5: [i8;6] = [10i8, 5, 2, 3, 7, 5];
const l6: [i8;5] = [4i8, -2, 3, 3, 4];
const l7: [i8;3] = [0i8, 2, 0];
const l8: [i8;4] = [5i8, 9, 13, -3];


#[test]
fn t1() {
    assert_eq!(sum_pairs(&l1, 8), Some((1, 7)));
}
#[test]
fn t2() {
    assert_eq!(sum_pairs(&l2, -6), Some((0, -6)));
}
#[test]
fn t3() {
    assert_eq!(sum_pairs(&l3, -7), None);
}
#[test]
fn t4() {
    assert_eq!(sum_pairs(&l4, 2), Some((1, 1)));
}
#[test]
fn t5() {
    assert_eq!(sum_pairs(&l5, 10), Some((3, 7)));
}
#[test]
fn t6() {
    assert_eq!(sum_pairs(&l6, 8), Some((4, 4)));
}
#[test]
fn t7() {
    assert_eq!(sum_pairs(&l7, 0), Some((0, 0)));
}
#[test]
fn t8() {
    assert_eq!(sum_pairs(&l8, 10), Some((13, -3)));
}
