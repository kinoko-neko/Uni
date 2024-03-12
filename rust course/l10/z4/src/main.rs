fn encode(msg: String, n: i32) -> Vec<i32> {
    let pomi = n.to_string();
    msg.chars().zip(pomi.chars().map(|d| (d as i32 -('0'  as i32) )).cycle()).map(|(a,b)| b+1 + ((a as i32) - 'a' as i32 ) ).collect()
}



fn main() {
    println!("Hello, world!");
    let pom = encode("alksjdlksjjiiii".to_string(),98);
    let pom2 = pom.iter().map( |x| x.to_string()).collect::<Vec<String> >().join(",");
    println!("{}",pom2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t0() {
        assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
    }
    #[test]
    fn t1() {
        assert_eq!(encode("masterpiece".to_string(), 1939), vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]);
    }
    #[test]
    fn t2() {
        assert_eq!(encode("meowmeow".to_string(),123), vec![14,7,18,24,15,8,16,25]);
    }
    #[test]
    fn t3() {
        assert_eq!(encode("ertyuio".to_string(),98), vec![14,26,29,33,30,17,24]);
    }
    #[test]
    fn t4() {
        assert_eq!(encode("alksjdlksjjiiii".to_string(),98), vec![10,20,20,27,19,12,21,19,28,18,19,17,18,17,18]);
    }
}
