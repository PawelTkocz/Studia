//https://www.codewars.com/kata/5467e4d82edf8bbf40000155
fn descending_order(x: u64) -> u64 {
    let mut digits = x.clone().
                       to_string().
                       chars().
                       collect::<Vec<char>>();
    digits.sort_unstable();
    digits.into_iter().
           rev().
           collect::<String>().
           parse::<u64>().
           unwrap()
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn returns_expected1() {
        assert_eq!(descending_order(0), 0);
    }

    #[test]
    fn returns_expected2() {
        assert_eq!(descending_order(1), 1);
    }

    #[test]
    fn returns_expected3() {
        assert_eq!(descending_order(15), 51);
    }

    #[test]
    fn returns_expected4() {
        assert_eq!(descending_order(1021), 2110);
    }

    #[test]
    fn returns_expected5() {
        assert_eq!(descending_order(123456789), 987654321);
    }

    #[test]
    fn returns_expected6() {
        assert_eq!(descending_order(145263), 654321);
    }

    #[test]
    fn returns_expected7() {
        assert_eq!(descending_order(1254859723), 9875543221);
    }

}
  
