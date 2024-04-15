fn encode(msg: String, n: i32) -> Vec<i32> {
    let digits = n.to_string()
                  .chars()
                  .map(|x| x.to_digit(10)
                            .unwrap() as i32)
                  .collect::<Vec<i32>>();
    msg.char_indices()
       .map(|x| digits[x.0 % digits.len()] + (x.1 as u32 - 'a' as u32 + 1) as i32)
       .collect()
}


fn main() {
}


#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test1() {
        assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
    }
    
    #[test]
    fn test2() {
        assert_eq!(encode("masterpiece".to_string(), 1939), vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]);
    }

    #[test]
    fn test3() {
        assert_eq!(encode("aaa".to_string(), 123), vec![2, 3, 4]);
    }

    #[test]
    fn test4() {
        assert_eq!(encode("abab".to_string(), 2), vec![3, 4, 3, 4]);
    }

    #[test]
    fn test5() {
        assert_eq!(encode("c".to_string(), 99), vec![12]);
    }
}