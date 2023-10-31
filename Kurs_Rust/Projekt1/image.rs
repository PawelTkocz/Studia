use std::{fs::File, io::Write};
#[derive(Clone, Copy)]

struct Pixel{
    red: u8,
    green: u8,
    blue: u8
}

impl Pixel{
    fn new(red: u8, green: u8, blue: u8) -> Pixel{
        Pixel { 
            red: red, 
            green: green, 
            blue: blue 
        }
    }
}

pub struct Image{
    width: u32,
    height: u32,
    pixels: Vec<Vec<Pixel>>
}

impl Image{
    
    pub fn new(width: u32, height: u32) -> Image{
        Image{
            width: width,
            height: height,
            pixels: vec![vec![Pixel::new(0, 0, 0); width as usize]; height as usize]
        }
    }

    pub fn set_pixel(&mut self, x: u32, y: u32, red: u8, green: u8, blue: u8){
        self.pixels[y as usize][x as usize].red = red;
        self.pixels[y as usize][x as usize].green = green;
        self.pixels[y as usize][x as usize].blue = blue;
    }

    pub fn write_to_file(&mut self, path: &str){
        let mut file = File::create(path).expect("Nie udało się utworzyć pliku");
        let header = format!("P3\n{} {}\n255\n", self.width, self.height);
        file.write_all(header.as_bytes()).expect("Nie udało się zapisać zawartości pliku");
        self.pixels.iter().for_each(|row|{
            row.iter().for_each(|p|{
                let values = format!("{} {} {}\n", p.red, p.green, p.blue);
                file.write_all(values.as_bytes()).expect("Nie udało się zapisać zawartości pliku");
            })
        })
    }
}

fn main() {
    let mut img = Image::new(4, 5);
    img.set_pixel(1, 2, 12, 13, 14);
    img.write_to_file("image.txt");
}
