fn john_and_ann(n: i32) -> (Vec<i32>, Vec<i32>) {
   let mut j: Vec<i32> = vec![0];
   let mut a: Vec<i32> = vec![1];
   for d in 1..n  {
       j.push( d as i32 - a[j[(d-1) as usize] as usize]);
       a.push( d as i32 - j[a[(d-1) as usize] as usize]);
    }
    (j, a)
}

fn john(n: i32) -> Vec<i32> {
    john_and_ann(n).0
}

fn ann(n: i32) -> Vec<i32> {
    john_and_ann(n).1
}

fn sum_john(n: i32) -> i32 {
    john(n).iter().sum()
}

fn sum_ann(n: i32) -> i32 {
    ann(n).iter().sum()
}

fn main() {
    println!("ann: {}",ann(100).iter().map(|&a| a.to_string()).collect::<Vec<String>>().join(", ") );
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_john() {
        assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
        assert_eq!(john(14), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
    }
    #[test]
    fn test_ann() {
        assert_eq!(ann(6), vec![1, 1, 2, 2, 3, 3]);
        assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
    }
    #[test]
    fn test_sum_john() {
        assert_eq!(sum_john(75), 1720);
        assert_eq!(sum_john(78), 1861);
    }
    #[test]
    fn test_sum_ann() {
        assert_eq!(sum_ann(115), 4070);
        assert_eq!(sum_ann(150), 6930);
    }
}

#[test]
fn t0() {
        assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
}
#[test]
fn t1() {
        assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
}
#[test]
fn t2() {
        assert_eq!(sum_ann(150), 6930);
}
#[test]
fn t3() {
        assert_eq!(sum_john(78), 1861);
}
#[test]
fn t4() {
        assert_eq!(sum_john(75), 1720);
}
