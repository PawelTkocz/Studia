use complex::Complex;
use image::Image;

mod complex;
mod image;

const MAX_ITER: u32 =  150;
const MAX_ABS: f64 = 2.0;
const WIDTH: u32 = 600;
const HEIGHT: u32 = 400;

fn mandelbrot(c: Complex) -> u32{
    let mut z = Complex::new(0.0, 0.0);
    let mut n = 0;
    while z.abs() <= MAX_ABS && n<MAX_ITER{
        z = z*z + c;
        n += 1;
    }
    n
}

fn draw_fractal(re_start: f64, re_end: f64, im_start: f64, im_end: f64, name: &str){
    let mut img = Image::new(WIDTH, HEIGHT);

    for y in 0..HEIGHT{
        for x in 0..WIDTH{
            let c = Complex::new(re_start + ((x as f64)/(WIDTH as f64))*(re_end-re_start), im_start + ((y as f64)/(HEIGHT as f64))*(im_end-im_start));
            let m = mandelbrot(c);
            let color: u8 = 255 - (m*255/MAX_ITER) as u8;
            img.set_pixel(x, y, color, color, color);
        }
    }
    img.write_to_file(name);
}

fn main() {
    draw_fractal(-2.0, 1.0, -1.0, 1.0, "mandelbrot1.ppm");
    draw_fractal(-0.6, 0.0, -0.95, -0.55, "mandelbrot2.ppm");
    draw_fractal(-0.9, -0.6, -0.3, -0.1, "mandelbrot3.ppm");
    draw_fractal(-0.74, -0.75, 0.132, 0.138, "mandelbrot4.ppm");
}
