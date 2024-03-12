fn longest(a1: &str, a2: &str) -> String {
    // your code
    return ('a'..'z').filter(|&x| (a1.contains(x) || a2.contains(x)) ).collect();
}

fn main() {

    println!("Hello, world!");
}

#[cfg(test)]
    mod tests {
    use super::longest;

    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn test1() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
    }
    #[test]
    fn test2() {
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
    }
    #[test]
    fn test3() {
        testing("aaaaaaaaaaaa", "aaaa", "a");
    }
     #[test]
    fn test4() {
        testing("aaaaaaaaaaaaa", "bb", "ab");
    }
    #[test]
    fn test5() {
        testing("popipopipopipo", "yippeeee", "eiopy");
    }
}
