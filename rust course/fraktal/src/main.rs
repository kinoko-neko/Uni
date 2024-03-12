
struct Image{
    pub size: (u32,u32),
    red: Vec<Vec<u8>>,
    green: Vec<Vec<u8>>,
    blue: Vec<Vec<u8>>
}

impl Image{
    fn new(size: (u32,u32)) -> Self{
      Self{
            size,
            red: vec![vec![0;size.1 as usize];size.0 as usize],
            green: vec![vec![0;size.1 as usize];size.0 as usize],
            blue: vec![vec![0;size.1 as usize];size.0 as usize]
        }
    }

    fn set(&mut self, p:(u32,u32), kol:(u8,u8,u8)){
        let x = p.0 as usize;
        let y = p.1 as usize;
        self.red[x][y] = kol.0;
        self.green[x][y] = kol.1;
        self.blue[x][y] = kol.2;
    }

    fn to_ppm(&self) -> String{
        let mut ret = "P3\n".to_string() + &self.size.0.to_string() + " "+ &self.size.1.to_string() + "\n255\n";
        for y in 0..self.size.1 as usize{
            for x in 0..self.size.0 as usize{
                ret = ret + &self.red[x][y].to_string() +" "+ &self.green[x][y].to_string()+" "+ &self.blue[x][y].to_string()+"\n";
            }
        }
        ret
    }
    fn zapisz(&self, nazwa:&str){
        use std::fs::File;
        use std::path::Path;
        use std::io::prelude::*;
        let path = Path::new(nazwa);
        let mut plik = match File::create(path) {
            Err(e) => panic!("nie dziala tworzenie pliku {}!!!!",e),
            Ok(plik) => plik,
        };
        match plik.write_all(self.to_ppm().as_bytes()) {
            Err(e) => panic!("nie dziala zapis {}!!!!",e),
            Ok(_) => println!("zapisano")
        }

    }
}

#[derive(Copy,Clone)]
struct Complex{
    real: f64,
    img: f64
}

impl Complex{
    fn new() ->Self {
        Self { real: 0.0, img: 0.0 }
    }

    fn from(x:f64,y:f64) -> Self {
        Self { real:x, img:y}
    }
    fn abssq(self) -> f64 {
        self.real*self.real + self.img*self.img
    }
}


use std::ops;

impl ops::Add<Complex> for Complex {
    type Output = Complex;

    fn add(self, rhs: Complex) ->Complex{
        Complex::from(self.real+rhs.real,self.img+rhs.img)
    }
}

impl ops::Sub<Complex> for Complex {
    type Output = Complex;

    fn sub(self, rhs: Complex) ->Complex{
        Complex::from(self.real-rhs.real,self.img-rhs.img)
    }
}

impl ops::Mul<Complex> for Complex {
    type Output = Complex;

    fn mul(self, rhs: Complex) ->Complex{
        let a = self.real;
        let b = self.img;
        let c = rhs.real;
        let d = rhs.img;
        Complex::from(a*c - b*d, a*d + b*c)
    }
}

impl ops::Div<Complex> for Complex {
    type Output = Complex;

    fn div(self, rhs: Complex) ->Complex{
        let a = self.real;
        let b = self.img;
        let c = rhs.real;
        let d = rhs.img;
        Complex::from((a*c+b*d)/(c*c+d*d), (b*c-a*d)/(d*d + c*c))
    }
}


fn main() {

    let mxcnt = 100;
    let x = 1000;
    let y = 1000;
    let mut cnt;
    let mut pic = Image::new((x,y));
    for i in 0..x{
        for j in 0..y{
         //   let mut z = Complex::from(-2.0+, )
            let c = Complex::from(-2.0+((i as f64)/(x as f64))*4.0,-2.0+((j as f64)/(y as f64))*4.0 );
            let mut z = Complex::new();
            cnt = 0;
            while z.abssq() <= 4.0 && cnt < mxcnt {
                z = z*z + c;
                cnt += 1;
            }
            if cnt < mxcnt{
                pic.set((i,j),(0,cnt,0))
            }
            else{
                pic.set((i,j),(0,0,0) )
            }
        }
    }
    pic.zapisz("frac2.ppm");
    println!("Hello, world!");
}

