
fn count_bits(n: i64) -> u32 {
 n.count_ones()
}

fn main() {
    let a= 123_i32.count_ones();
    println!("{}",a);
}



#[cfg(test)]
mod tests {
    use super::count_bits;

    #[test]
    fn test1() {
        assert_eq!(count_bits(0), 0);
    }
    #[test]
    fn test2() {
        assert_eq!(count_bits(4), 1);
    }
    #[test]
    fn test3() {
        assert_eq!(count_bits(7), 3);
    }
    #[test]
    fn test4() {
        assert_eq!(count_bits(9), 2);
    }
    #[test]
    fn test5() {
        assert_eq!(count_bits(10), 2);
    }
}

