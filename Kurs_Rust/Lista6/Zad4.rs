//https://www.codewars.com/kata/59cfc000aeb2844d16000075
fn capitalize(s: &str) -> Vec<String> {
    let mut str1: Vec<char> = vec![];
    let mut str2: Vec<char> = vec![];

    for(i, c) in s.chars().
                                into_iter().
                                enumerate(){
        if i%2 == 0{
            str1.push(c.to_ascii_uppercase());
            str2.push(c);
        }
        else{
            str2.push(c.to_ascii_uppercase());
            str1.push(c);
        }
    }
    vec![str1.iter().collect(), str2.iter().collect()]
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn example_tests1() {
        assert_eq!(capitalize("abcdef"),["AbCdEf", "aBcDeF"]);
    }

    #[test]
    fn example_tests2() {
        assert_eq!(capitalize("codewars"),["CoDeWaRs", "cOdEwArS"]);
    }

    #[test]
    fn example_tests3() {
        assert_eq!(capitalize("abracadabra"),["AbRaCaDaBrA", "aBrAcAdAbRa"]);
    }

    #[test]
    fn example_tests4() {
        assert_eq!(capitalize("codewarriors"),["CoDeWaRrIoRs", "cOdEwArRiOrS"]);
    }

    #[test]
    fn example_tests5() {
        assert_eq!(capitalize("helloworld"),["HeLlOwOrLd", "hElLoWoRlD"]);
    }

}
