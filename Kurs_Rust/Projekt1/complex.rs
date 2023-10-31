use std::ops::{Add, Sub, Mul};

#[derive(Copy, Clone)]
pub struct Complex{
    real: f64,
    imaginary: f64
}

impl Add for Complex{
    type Output = Self;
    
    fn add(self, other: Self) -> Self{
        Self{
            real: self.real + other.real,
            imaginary: self.imaginary + other.imaginary
        }
    }
}

impl Sub for Complex{
    type Output = Self;

    fn sub(self, other: Self) -> Self{
        Self{
            real: self.real - other.real,
            imaginary: self.imaginary - other.imaginary
        }
    }    
}

impl Mul for Complex{
    type Output = Self;

    fn mul(self, other: Self) -> Self{
        Self{
            real: self.real*other.real - self.imaginary*other.imaginary,
            imaginary: self.real*other.imaginary + self.imaginary*other.real
        }
    }    
}

impl Complex{ 
    pub fn new(real: f64, imaginary: f64) -> Complex{
        Complex{
            real: real,
            imaginary: imaginary
        }
    }

    pub fn abs(self) -> f64{
        (self.real*self.real + self.imaginary*self.imaginary).sqrt()
    }
}

fn main() {
    let x = Complex::new(4.5, 3.4);
    let y = Complex::new(7.1, -11.9);
    let z = x + y;
    let a = x - y;
    let b = x*y;
    print!("{} {} {} {} {} {}", z.real, z.imaginary, a.real, a.imaginary, b.real, b.imaginary);
}
