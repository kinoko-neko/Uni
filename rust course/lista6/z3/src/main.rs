fn hamming(n: usize) -> u64 {
    let mut wsk = [0,0,0]; // wskazniki na najmniejszy ham ktory jeszcze nie byl pomnozonyprze przez dana liczbe
    let mut ham = vec![1];
    for _i in 1..n {
        let cand = [ham[wsk[0]]*2,ham[wsk[1]]*3,ham[wsk[2]]*5 ];
        let next = cand.into_iter().min().unwrap();
        ham.push(next);
        for j in 0..3{
            if cand[j]==next{
                wsk[j]+=1;
            }
        }
    }
    ham[n-1]
}
fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::hamming;

    #[test]
    fn t1() {
        assert_eq!(hamming(1), 1);
    }
    #[test]
    fn t2() {
        assert_eq!(hamming(2), 2);
    }
    #[test]
    fn t3() {
        assert_eq!(hamming(3), 3);
    }
    #[test]
    fn t4() {
        assert_eq!(hamming(4), 4);
    }
    #[test]
    fn t5() {

        assert_eq!(hamming(19), 32);
    }
}
