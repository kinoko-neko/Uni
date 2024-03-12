fn summy(strng: &str) -> i32 {
    strng.split(' ').map(|x| x.parse::<i32>().unwrap()).sum()
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::summy;

    #[test]
    fn test1() {
        assert_eq!(summy("1 2 3"), 6);
    }
    #[test]
    fn test2() {
        assert_eq!(summy("1 2 3 4"), 10);
    }
    #[test]
    fn test3() {
        assert_eq!(summy("1 2 3 4 5"), 15);
    }
    #[test]
    fn test4() {
        assert_eq!(summy("10 10"), 20);
    }
    #[test]
    fn test5() {
        assert_eq!(summy("0 0"), 0);
    }
}
