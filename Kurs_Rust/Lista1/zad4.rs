fn printer_error(s: &str) -> String {
    let cnt = s.chars()
                      .filter(|c| c > &'m')
                      .collect::<Vec<char>>()
                      .len();
    format!("{}/{}", cnt, s.len())
}

fn main() {

}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test1() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
    }

    #[test]
    fn test2() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
    }

    #[test]
    fn test3() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }

    #[test]
    fn test4() {
        assert_eq!(&printer_error("aaabbbbhaijjjm"), "0/14");
    }

    #[test]
    fn test5() {
        assert_eq!(&printer_error("knkjvappafadskfj"), "5/16");
    }
}