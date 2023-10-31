fn main() {
    
}

fn get_count(string: &str) -> usize {
    let vowels = vec!['a', 'e', 'i', 'o', 'u'];
    return string.chars()
                 .filter(|x| vowels.contains(x))
                 .count();
}



#[cfg(test)]
mod tests {
    use super::get_count;
    
    #[test]
    fn my_test1() {
        assert_eq!(get_count("abracadabra"), 5);
    }

    #[test]
    fn my_test2() {
        assert_eq!(get_count("little cat"), 3);
    }

    #[test]
    fn my_test3() {
        assert_eq!(get_count("interesting dog"), 5);
    }

    #[test]
    fn my_test4() {
        assert_eq!(get_count("fast turtle"), 3);
    }

    #[test]
    fn my_test5() {
        assert_eq!(get_count("fkdjlk;"), 0);
    }
}