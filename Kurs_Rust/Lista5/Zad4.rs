fn expanded_form(n: u64) -> String {
    let mut res: Vec<String> = vec![];
    for (i, dig) in n.to_string().
                      chars().
                      into_iter().
                      enumerate(){
        if dig != '0'{
            res.push(dig.to_string().
                         clone() + vec!['0' as char; n.to_string().len() - i - 1].iter().
                                                                                  collect::<String>().
                                                                                  as_str());
        }
    }
    res.join(" + ")
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        assert_eq!(expanded_form(12), "10 + 2");
    }

    #[test]
    fn test2() {
        assert_eq!(expanded_form(42), "40 + 2");
    }

    #[test]
    fn test3() {
        assert_eq!(expanded_form(70304), "70000 + 300 + 4");
    }

    #[test]
    fn test4() {
        assert_eq!(expanded_form(1), "1");
    }

    #[test]
    fn test5() {
        assert_eq!(expanded_form(999), "900 + 90 + 9");
    }
}
