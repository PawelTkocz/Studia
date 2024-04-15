//https://www.codewars.com/kata/6512b3775bf8500baea77663
fn gimme_the_letters(sp: &str) -> String {
    let first = sp.chars().next().unwrap();
    let last = sp.chars().last().unwrap();
    (first..=last).collect()
}


fn main() {
}


#[cfg(test)]
mod tests {
    use super::gimme_the_letters;
        
    fn dotest(sp: &str, expected: &str) {
        let actual = gimme_the_letters(sp);
        assert!(actual == expected, 
            "With sp = \"{sp}\"\nExpected \"{expected}\" but got \"{actual}\"")
    }

    #[test]
    fn test1() {
        dotest("a-z", "abcdefghijklmnopqrstuvwxyz");
    }

    #[test]
    fn test2() {
        dotest("h-o", "hijklmno");
    }

    #[test]
    fn test3() {
        dotest("Q-Z", "QRSTUVWXYZ");
    }

    #[test]
    fn test4() {
        dotest("J-J", "J");
    }

    #[test]
    fn test5() {
        dotest("a-b", "ab");
    }

    #[test]
    fn test6() {
        dotest("A-A", "A");
    }

    #[test]
    fn test7() {
        dotest("g-i", "ghi");
    }

    #[test]
    fn test8() {
        dotest("H-I", "HI");
    }

    #[test]
    fn test9() {
        dotest("y-z", "yz");
    }

    #[test]
    fn test10() {
        dotest("e-k", "efghijk");
    }
    #[test]
    fn test11() {
        dotest("a-q", "abcdefghijklmnopq");
    }
    #[test]
    fn test12() {
        dotest("F-O", "FGHIJKLMNO");
    }
}
