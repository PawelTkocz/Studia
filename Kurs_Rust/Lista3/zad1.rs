fn row_sum_odd_numbers(n:i64) -> i64 {
    n*n*n    
}

fn main() {
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn returns_expected1() {
      assert_eq!(row_sum_odd_numbers(1), 1);
    }

    #[test]
    fn returns_expected2() {
        assert_eq!(row_sum_odd_numbers(42), 74088);
    }

    #[test]
    fn returns_expected3() {
        assert_eq!(row_sum_odd_numbers(2), 8);
    }

    #[test]
    fn returns_expected4() {
        assert_eq!(row_sum_odd_numbers(3), 27);
    }

    #[test]
    fn returns_expected5() {
        assert_eq!(row_sum_odd_numbers(4), 64);
    }
}
