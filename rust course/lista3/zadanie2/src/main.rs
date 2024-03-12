fn number(bus_stops:&[(i32,i32)]) -> i32 {
    bus_stops.into_iter().map(|x| x.0-x.1).sum()
}

fn main() {
    println!("Hello, world!");
}


#[cfg(test)]
    mod tests {
    use super::number;

    #[test]
    fn test1() {
        assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
    }
    #[test]
    fn test2() {
        assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
    }
    #[test]
    fn test3() {
        assert_eq!(number(&[(3,0),(9,1),(4,8),(12,2),(6,1),(7,8)]), 21);
    }
    #[test]
    fn test4() {
        assert_eq!(number(&[(5,0),(0,5)]), 0);
    }
    #[test]
    fn test5() {
        assert_eq!(number(&[(0,0),(19,0),(8,7)]), 20);
    }
     #[test]
    fn test6() {
        assert_eq!(number(&[(1,0),(7,0),(1,7)]), 2);
    }
     #[test]
    fn test7() {
        assert_eq!(number(&[(0,0),(19,0)]), 19);
    }
     #[test]
    fn test8() {
        assert_eq!(number(&[(20,0),(0,20),(19,0),(8,7)]), 20);
    }
     #[test]
    fn test9() {
        assert_eq!(number(&[(19,0),(0,0),(19,9),(8,7)]), 30);
    }
     #[test]
    fn test10() {
        assert_eq!(number(&[(210,0),(19,0),(8,7)]), 230);
    }
}
