struct Sudoku{
    data: Vec<Vec<u32>>,
}


impl Sudoku{
    fn is_valid(&self) -> bool {
        let n = self.data.len();
        let sq = (n as f64).sqrt() as usize;
        //sprawdz dlugosc wierszy
        for i in 0..n{
            if self.data[i].len() != n {
                return false;
            }
        }

        //sprawdz zakres
        for i in 0..n {
            for j in 0..n {
                if self.data[i][j] == 0 || self.data[i][j] >n as u32{
                    return false;
                }
            }
        }

        let mut v = vec![0; n+1];
        let mut cnt = 0;

        for i in 0..n {
            for j in 0..n {
                if v[ (self.data[i as usize][j as usize]-1) as usize] != cnt {
                    return false;
                }
                v[ (self.data[i as usize][j as usize]-1) as usize] +=1;
            }
            cnt+=1;
            for j in 0..n {
                if v[ (self.data[j as usize][i as usize]-1) as usize] != cnt {
                    return false;
                }
                v[(self.data[j as usize][i as usize]-1) as usize] +=1;
            }
            cnt +=1;
        }

        for i in (0..n).step_by(sq as usize){
            for j in (0..n).step_by(sq as usize){
                for i2 in 0..sq{
                    for j2 in 0..sq{
                        if v[(self.data[(i+i2) as usize][j+j2]-1) as usize] != cnt {
                            return false;
                        }
                        v[(self.data[i+i2][j+j2]-1) as usize] +=1;
                    }
                }
                cnt += 1;
            }
        }
        true
      //sprawdz czy wiersze kolumny o
    }
}

fn main() {
    println!("Hello, world!");
}

#[test]
fn t0() {
    assert!(Sudoku{
        data: vec![
                vec![7,8,4, 1,5,9, 3,2,6],
                vec![5,3,9, 6,7,2, 8,4,1],
                vec![6,1,2, 4,3,8, 7,5,9],

                vec![9,2,8, 7,1,5, 4,6,3],
                vec![3,5,7, 8,4,6, 1,9,2],
                vec![4,6,1, 9,2,3, 5,8,7],

                vec![8,7,6, 3,9,4, 2,1,5],
                vec![2,4,3, 5,6,1, 9,7,8],
                vec![1,9,5, 2,8,7, 6,3,4]
            ]
}.is_valid());
}

#[test]
fn t1() {
    assert!(Sudoku{
        data: vec![
                vec![1, 4,  2, 3],
                vec![3, 2,  4, 1],

                vec![4, 1,  3, 2],
                vec![2, 3,  1, 4],
            ]
}.is_valid());
}

#[test]
fn t2() {
    assert!(!Sudoku{
        data: vec![
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],

                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],

                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
            ]
}.is_valid());
}

#[test]
fn t3() {
    assert!(!Sudoku{
        data: vec![
                vec![1,2,3,4,5],
                vec![1,2,3,4],
                vec![1,2,3,4],
                vec![1],
            ]
}.is_valid());
}

#[test]
fn t4() {
    assert!(Sudoku{
        data: vec![
                vec![1],
            ]
}.is_valid());
}
