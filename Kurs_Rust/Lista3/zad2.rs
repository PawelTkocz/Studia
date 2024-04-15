//https://www.codewars.com/kata/5648b12ce68d9daa6b000099
fn number(bus_stops:&[(i32,i32)]) -> i32 {
    bus_stops.iter()
             .map(|s| s.0 - s.1)
             .sum()
}

fn main() {
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn returns_expected1() {
        assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
    }

    #[test]
    fn returns_expected2() {
        assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
    }

    #[test]
    fn returns_expected3() {
        assert_eq!(number(&[(3,0),(9,1),(4,8),(12,2),(6,1),(7,8)]), 21);
    }

    #[test]
    fn returns_expected4() {
        assert_eq!(number(&[(3,0)]), 3);
    }

    #[test]
    fn returns_expected5() {
        assert_eq!(number(&[(9,0),(2,9),(10,2)]), 10);
    }
}
  
