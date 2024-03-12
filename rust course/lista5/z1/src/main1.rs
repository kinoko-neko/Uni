fn count_odd_pentafib(n: u16) -> u16 {
    let t = [0,1,2,2,2,2];
    // (n/6)*2 + mod -1
    (n/6)*2 + t[(n%6) as usize] -std::cmp::min(1,std::cmp::max(0,(n as i32)-1i32)) as u16
}

fn main() {
    println!("Hello, world!");
}

// Add your tests here.
// See https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html

#[cfg(test)]
mod tests {
    use super::count_odd_pentafib;

    #[test]
    fn t1(){
        assert_eq!(count_odd_pentafib(5), 1);
    }
    #[test]
    fn t2(){
        assert_eq!(count_odd_pentafib(10), 3);
    }
    #[test]
    fn t3(){
        assert_eq!(count_odd_pentafib(15), 5);
    }
    #[test]
    fn t4(){
        assert_eq!(count_odd_pentafib(45), 15);
    }
    #[test]
    fn t5(){
        assert_eq!(count_odd_pentafib(68), 23);
    }
    #[test]
    fn t6(){
        assert_eq!(count_odd_pentafib(0), 0);
    }
    #[test]
    fn t7(){
        assert_eq!(count_odd_pentafib(1), 1);
    }
    #[test]
    fn t8(){
        assert_eq!(count_odd_pentafib(2), 1);
    }
}
