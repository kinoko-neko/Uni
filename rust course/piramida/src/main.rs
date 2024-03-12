
fn wzor(m:u32) -> u32{
    let n = m as u64;
    return ((n*(n+1)*(2*n+1)) / 6 ) as u32
}

fn beeramid (bonus: i32, price: f32) -> usize {
    let piwa: u32 = ((bonus as f32)/ price ) as u32;

    if piwa < 1{
        return 0 as usize
    }

 //   println!("piwa {}",piwa);

    let est: u32 = ((piwa*3) as f32).cbrt() as u32 ;
    if wzor(est)> piwa {
        return (est-1) as usize;
    }
    est as usize
}

fn main() {
    println!("{}\n{}\n{}",beeramid(9, 2.0), beeramid(10, 2.0),beeramid(4, 4.0));
}
