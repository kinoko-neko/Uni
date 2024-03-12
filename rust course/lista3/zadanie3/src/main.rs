struct Cipher {
  //your code here
    plain:  String,
    enc: String
}

impl Cipher {
  fn new(map1: &str, map2: &str) -> Cipher {
    //your code here
       Cipher{
        plain: map1.to_string(),
        enc: map2.to_string(),
      }
  }

  fn encode(&self, string: &str) -> String {
    //your code here
      string.to_string().chars().map(|x|
          match self.plain.contains(x) {
                true => self.enc.chars().nth(self.plain.chars().position(|y| y==x).unwrap()).unwrap(),
                _ => x
            }
    ).collect()

  }

  fn decode(&self, string: &str) -> String {
    string.to_string().chars().map(|x|
          match self.enc.contains(x) {
                true => self.plain.chars().nth(self.enc.chars().position(|y| y==x).unwrap()).unwrap(),
                _ => x
            }
    ).collect()
  }
}

fn main() {
    println!("Hello, world!");
}


#[cfg(test)]
    mod tests {
    use super::Cipher;

    #[test]
    fn test1() {
        let map1 = "abcdefghijklmnopqrstuvwxyz";
        let map2 = "etaoinshrdlucmfwypvbgkjqxz";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.encode("abc"), "eta");
    }
    #[test]
    fn test2() {
        let map1 = "abcdefghijklmnopqrstuvwxyz";
        let map2 = "etaoinshrdlucmfwypvbgkjqxz";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.encode("xyz"), "qxz");
    }
    #[test]
    fn test3() {
        let map1 = "abcdefghijklmnopqrstuvwxyz";
        let map2 = "etaoinshrdlucmfwypvbgkjqxz";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("eirfg"), "aeiou");
    }
    #[test]
    fn test4() {
        let map1 = "abcdefghijklmnopqrstuvwxyz";
        let map2 = "etaoinshrdlucmfwypvbgkjqxz";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("erlang"), "aikcfu");
    }

    #[test]
    fn test5() {
        let map1 = "argh";
        let map2 = "uiog";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("uiog"), "argh");
    }
     #[test]
    fn test6() {
        let map1 = "argh";
        let map2 = "uiog";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("qq"), "qq");
    }
     #[test]
    fn test7() {
        let map1 = "qwerty";
        let map2 = "abcdef";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("bada"), "wqrq");
    }
      #[test]
    fn test8() {
        let map1 = "asdfghjkl";
        let map2 = "zxcvbnmpo";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("sampo"), "sajkl");
    }
      #[test]
    fn test9() {
        let map1 = "qazwsxedc";
        let map2 = "plmoknijb";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("plomba"), "qawzca");
    }
      #[test]
    fn test10() {
        let map1 = "asdfghjkp";
        let map2 = "atimvqnjk";

        let cipher = Cipher::new(map1, map2);

        assert_eq!(cipher.decode("tai"), "sad");
    }
}


