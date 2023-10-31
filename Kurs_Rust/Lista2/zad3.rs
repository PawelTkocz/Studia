fn summy(strng: &str) -> i32 {
    strng.split(' ')
         .map(|x| x.parse::<i32>().unwrap())
         .sum()
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_test1() {
        assert_eq!(summy("1 2 3"), 6);
    }

    #[test]
    fn sample_test2() {
        assert_eq!(summy("1 2 3 4"), 10);
    }

    #[test]
    fn sample_test3() {
        assert_eq!(summy("1 2 3 4 5"), 15);
    }

    #[test]
    fn sample_test4() {
        assert_eq!(summy("10 10"), 20);
    }

    #[test]
    fn sample_test5() {
        assert_eq!(summy("0 0"), 0);
    }
}