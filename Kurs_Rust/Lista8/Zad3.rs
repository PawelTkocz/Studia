fn part_list(arr: Vec<&str>) -> String {
    let mut res = vec![];
    for i in 1..arr.len(){
        res.push((&arr[0..i], &arr[i..]));
    }
    res.iter()
       .map(|x| format!("({}, {})", x.0.join(" "), x.1.join(" ")))
       .collect::<Vec<String>>()
       .join("")
}

fn main() {
}

#[cfg(test)]
    mod tests {
    use super::*;

    fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn test1() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
                "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
    }

    #[test]
    fn test2() {
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"], 
            "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");    
    }

    #[test]
    fn test3() {
        dotest(vec!["one", "two"], 
            "(one, two)");    
    }

    #[test]
    fn test4() {
        dotest(vec!["one", "two", "three"], 
            "(one, two three)(one two, three)");    
    }

    #[test]
    fn test5() {
        dotest(vec!["a", "b", "c", "d"], 
            "(a, b c d)(a b, c d)(a b c, d)");    
    }
}

