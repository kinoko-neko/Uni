mod solution {

    pub fn range_extraction(a: &[i32]) -> String {
        let mut ret = vec![];
        let mut inc = vec![];
        inc.push(a[0].to_string());

        a[1..].iter().for_each(|&x| {
       //     println!("{}",x);
            let ls = inc.last().unwrap().parse::<i32>().unwrap();
            if x != ls+1 {
                if inc.len()<3{
                    ret.append(&mut inc);
                }
                else{
                    ret.push(format!("{}-{}",inc[0],inc.last().unwrap()))
                }
                inc = vec![];
            }
            inc.push(x.to_string());
        });

        if inc.len()<3{
            ret.append(&mut inc);
        }
        else{
            ret.push(format!("{}-{}",inc[0],inc.last().unwrap()))
        }
      //  println!("{}",ret.len());
        ret.join(",")
     //   "".to_string()
    }
}

fn main(){
    println!("{}",solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]));
}
#[cfg(test)]
mod tests {
    use super::*;


    #[test]
    fn t1() {
        assert_eq!(solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]), "-6,-3-1,3-5,7-11,14,15,17-20");
    }
#[test]
fn t2() {
        assert_eq!(solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]), "-3--1,2,10,15,16,18-20");
    }
    #[test]
fn t3() {
        assert_eq!(solution::range_extraction(&[1,2,3,4,5,6]), "1-6");
    }
    #[test]
fn t4() {
        assert_eq!(solution::range_extraction(&[0,1]), "0,1");
    }
    #[test]
fn t5() {
        assert_eq!(solution::range_extraction(&[1]), "1");
    }
}
