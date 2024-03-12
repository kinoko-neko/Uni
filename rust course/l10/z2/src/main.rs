fn dig_pow(n: i64, p: i32) -> i64 {
    // your code
    let suma = n.to_string().chars().enumerate().map(|(i, c)| (c.to_digit(10).unwrap() as i128).pow(i as u32 + (p as u32) )).sum::<i128>();

    match suma % (n as i128){
        0 => (suma / (n as i128) )as i64,
        _ => -1
    }
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
    mod tests {
    use super::*;

    fn dotest(n: i64, p: i32, exp: i64) -> () {
        println!(" n: {:?};", n);
        println!("p: {:?};", p);
        let ans = dig_pow(n, p);
        println!(" actual:\n{:?};", ans);
        println!("expect:\n{:?};", exp);
        println!(" {};", ans == exp);
        assert_eq!(ans, exp);
        println!("{};", "-");
    }

    #[test]
    fn t0() {
        dotest(89, 1, 1);
    }
    #[test]
    fn t1() {
        dotest(92, 1, -1);
    }
    #[test]
    fn t2() {
        dotest(46288, 3, 51);
    }
    #[test]
    fn t3() {
        dotest(1377, 1, 2);
    }
    #[test]
    fn t4() {
        dotest(6714, 3, 1);
    }
}
