fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    // Good luck
    let a:Vec<i32> = array.iter().filter(|&x| (x%2)==0 ).map(|x| x.to_owned()).collect();
    a[a.len()-number..].to_vec()
}

fn main() {
    even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3);
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1(){
        assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
    }
    #[test]
    fn t2(){
        assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
    }
    #[test]
    fn t3(){
        assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
    }
    #[test]
    fn t4(){
        assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23,10,12), 3), vec!(6,10,12));
    }
    #[test]
    fn t5(){
        assert_eq!(even_numbers(&vec!(-6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(-6));
    }
}
