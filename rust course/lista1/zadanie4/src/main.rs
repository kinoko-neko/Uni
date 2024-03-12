fn printer_error(s: &str) -> String {
    format!("{}/{}",s.chars().filter(|&x| x>'m' ).count(),s.len())
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
    }
    #[test]
    fn test2() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
    }
    #[test]
    fn test3() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }
    #[test]
    fn test4() {
        assert_eq!(&printer_error("a"), "0/1");
    }
    #[test]
    fn test5() {
        assert_eq!(&printer_error("nn"), "2/2");
    }
    #[test]
    fn test6() {
        assert_eq!(&printer_error(""), "0/0");
    }

}
