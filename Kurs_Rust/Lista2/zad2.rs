fn longest(a1: &str, a2: &str) -> String {
    ('a'..='z').filter(|&x| a1.contains(x) || a2.contains(x))
               .collect()
}

fn main(){

}

#[cfg(test)]
mod tests {
    use super::*;
   
    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn basic_test1() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
    }

    #[test]
    fn basic_test2() {
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
    }

    #[test]
    fn basic_test3() {
        testing("fsdadab", "afifefadfk", "abdefiks");
    }

    #[test]
    fn basic_test4() {
        testing("fhsjdfhdld", "dsfhsdfhure", "defhjlrsu");
    }

    #[test]
    fn basic_test5() {
        testing("fjlajgdlsjbjslfscjfslhdreffsgljgh", "jkfdaildfjamafan", "abcdefghijklmnrs");
    }
}
