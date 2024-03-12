fn capitalize(s: &str) -> Vec<String> {
  //  s.chars().enumerate().map(|(x,y)| if x%2==0 {y.to_lowercase().to_string()} else {y.to_uppercase().to_string()});

    vec![s.chars().enumerate().map(|(x,y)| if x%2==1 {y.to_lowercase().to_string()} else {y.to_uppercase().to_string()}).collect::<String>(),
        s.chars().enumerate().map(|(x,y)| if x%2==0 {y.to_lowercase().to_string()} else {y.to_uppercase().to_string()}).collect::<String>()]

}

fn main() {
    println!("Hello, world!");
}
// Add your tests here.
// See https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1(){
        assert_eq!(capitalize("abcdef"),["AbCdEf", "aBcDeF"]);
    }
    #[test]
    fn t2(){
        assert_eq!(capitalize("codewars"),["CoDeWaRs", "cOdEwArS"]);
        }
    #[test]
    fn t3(){
        assert_eq!(capitalize("abracadabra"),["AbRaCaDaBrA", "aBrAcAdAbRa"]);
    }
    #[test]
    fn t4(){
        assert_eq!(capitalize("codewarriors"),["CoDeWaRrIoRs", "cOdEwArRiOrS"]);
    }
    #[test]
    fn t5(){
        assert_eq!(capitalize("A"),["A", "a"]);
    }
}
