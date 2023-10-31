use std::f64::consts::PI;

fn square_area_to_circle(size:f64) -> f64 {
    PI*size/4.0
}

fn main(){

}

#[cfg(test)]
mod tests {
    use super::square_area_to_circle;
    
    fn assert_close(a:f64, b:f64, epsilon:f64) {
        assert!( (a-b).abs() < epsilon, "Expected: {}, got: {}",b,a);
    }
    
    #[test]
    fn returns_expected1() {
        assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
    }

    #[test]
    fn returns_expected2() {
        assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
    }

    #[test]
    fn returns_expected3() {
        assert_close(square_area_to_circle(1.0), 0.78539816339744, 1e-8);
    }

    #[test]
    fn returns_expected4() {
        assert_close(square_area_to_circle(100.0), 78.5398163397448, 1e-8);
    }

    #[test]
    fn returns_expected5() {
        assert_close(square_area_to_circle(55.0), 43.1968989868596, 1e-8);
    }
}