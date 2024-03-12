fn first_n_smallest (arr: &[i32], n: usize) -> Vec<i32> {
    let mut pom: Vec<(i32,u32)> = arr.iter().enumerate().map(|x | (*x.1,x.0 as u32)).collect::<Vec<(i32,u32)>>();
    pom.sort();
    let mut pom2: Vec<(u32,i32)> = pom[0..n].iter().map(|x| (x.1,x.0)).collect();
    pom2.sort();
    pom2.iter().map(|x| x.1).collect::<Vec<i32> >()
}

fn main() {
    println!("Hello, world!");
}

// Add your tests here.
// See https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html

#[test]
fn test0() {
    assert_eq!(first_n_smallest(&[1,2,3,4,5],3), [1,2,3]);
}
#[test]
fn test1() {
        assert_eq!(first_n_smallest(&[5,4,3,2,1],3), [3,2,1]);
        }
#[test]
fn test2() {
        assert_eq!(first_n_smallest(&[1,2,3,1,2],3), [1,2,1]);
        }
#[test]
fn test3() {
        assert_eq!(first_n_smallest(&[1,2,3,-4,0],3), [1,-4,0]);
        }
#[test]
fn test4() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],0), []);
        }
#[test]
fn test5() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],5), [1,2,3,4,5]);
}
