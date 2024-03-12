fn is_vowel(s: char) -> bool {
  // /  let gloski="aeiou";
    "aeiou".contains(s)
}

fn get_count(string: &str) -> usize {
  //let mut vowels_count: usize = 0;

  // Do your magic here

  let vowels_count=string.chars().filter(|&x| is_vowel(x) ).count();
    return vowels_count;
}


fn main() {
    println!("Hello, world!");
    get_count("a");
}

#[cfg(test)]
mod tests {
    use super::get_count;

    #[test]
    fn test1() {
        assert_eq!(get_count("abracadabra"), 5);
    }
    #[test]
    fn test2() {
        assert_eq!(get_count("grzyb"), 0);
    }
    #[test]
    fn test3() {
        assert_eq!(get_count("aiueo"), 5);
    }
    #[test]
    fn test4() {
        assert_eq!(get_count("yyyyyyyyyyy"), 0);
    }
    #[test]
    fn test5() {
        assert_eq!(get_count("adef"), 2);
    }
}
