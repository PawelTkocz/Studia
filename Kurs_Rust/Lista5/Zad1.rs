fn count_odd_pentafib(n: u16) -> u16 {
    if n<1{
        return 0;
    }
    else if n<6{
        return 1;
    }
    if n%6 < 1{
        n/6*2 - 1
    }
    else if n%6 < 2{
        n/6*2 
    }
    else{
        n/6*2 + 1
    }
}


fn main() {

}

#[cfg(test)]
mod tests {
    use super::count_odd_pentafib;

    #[test]
    fn test1() {
        assert_eq!(count_odd_pentafib(5), 1);
    }
    
    #[test]
    fn test2() {
        assert_eq!(count_odd_pentafib(10), 3);
    }

    #[test]
    fn test3() {
        assert_eq!(count_odd_pentafib(15), 5);
    }

    #[test]
    fn test4() {
        assert_eq!(count_odd_pentafib(45), 15);
    }

    #[test]
    fn test5() {
        assert_eq!(count_odd_pentafib(68), 23);
    }
    
    #[test]
    fn test6() {
        assert_eq!(count_odd_pentafib(0), 0);
    }
    
    #[test]
    fn test7() {
        assert_eq!(count_odd_pentafib(1), 1);
    }
        
    #[test]
    fn test8() {
        assert_eq!(count_odd_pentafib(2), 1);
    }
}
