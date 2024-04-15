fn reverse_words(str: &str) -> String {
    str.split(" ").
        map(|w| w.chars().
                  rev().
                  collect::<String>()).
        collect::<Vec<String>>().
        join(" ")
}

fn main() {
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sample_test1() {
    assert_eq!(reverse_words("The quick brown fox jumps over the lazy dog."), "ehT kciuq nworb xof spmuj revo eht yzal .god");
    }   

    #[test]
    fn sample_test2() {
    assert_eq!(reverse_words("apple"), "elppa");
    } 

    #[test]
    fn sample_test3() {
    assert_eq!(reverse_words("a b c d"),"a b c d");
    } 

    #[test]
    fn sample_test4() {
    assert_eq!(reverse_words("double  spaced  words"), "elbuod  decaps  sdrow");
    } 

    #[test]
    fn sample_test5() {
    assert_eq!(reverse_words(" ma na ta am "), " am an at ma ");
    } 
}