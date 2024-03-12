fn expanded_form(n: u64) -> String {
    n.to_string().chars().enumerate().map( |(x,y)| {if(y!='0'){y.to_string()+&("0".repeat((n.to_string().len()-1 as usize)-x)) } else {if(n==0){"0".to_string()} else{"".to_string()} }}).filter(|x| x!="").collect::<Vec<String>>().join(" + ")
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;


    #[test]
    fn t1() {
        assert_eq!(expanded_form(12), "10 + 2");
    }
    #[test]
    fn t2() {
        assert_eq!(expanded_form(42), "40 + 2");
    }
    #[test]
    fn t3() {
        assert_eq!(expanded_form(70304), "70000 + 300 + 4");
    }
    #[test]
    fn t4() {
        assert_eq!(expanded_form(123), "100 + 20 + 3");
    }
    #[test]
    fn t5() {
        assert_eq!(expanded_form(0), "0");
    }
}
