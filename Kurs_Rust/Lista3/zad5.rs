//https://www.codewars.com/kata/5511b2f550906349a70004e1
fn nth_in_cycle(cycle: &str, n: u32) -> i32{
    cycle.chars()
         .nth(n as usize)
         .unwrap()
         .to_digit(10)
         .unwrap() as i32
}

fn mod_2(str: &str) -> u32{
    str[str.len()-1..].parse::<u32>()
                      .unwrap() % 2
}

fn mod_4(str: &str) -> u32{
    str[str.len()-2..str.len()].parse::<u32>()
                               .unwrap() % 4
}

fn last_digit(str1: &str, str2: &str) -> i32 {
    if str2 == "0"{
        return 1;
    }
    match str1[str1.len()-1..].parse::<u32>()
                              .unwrap(){
        1 => 1,
        2 => nth_in_cycle("6248", mod_4(str2)),
        3 => nth_in_cycle("1397", mod_4(str2)),
        4 => nth_in_cycle("64", mod_2(str2)),
        5 => 5,
        6 => 6,
        7 => nth_in_cycle("1793", mod_4(str2)),
        8 => nth_in_cycle("6842", mod_4(str2)),
        9 => nth_in_cycle("19", mod_2(str2)),
        _ => 0
    }
}

fn main() {
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn returns_expected1() {
      assert_eq!(last_digit("4", "1"), 4);
    }
    
    #[test]
    fn returns_expected2() {
      assert_eq!(last_digit("4", "2"), 6);
    }

    #[test]
    fn returns_expected3() {
      assert_eq!(last_digit("9", "7"), 9);
    }

    #[test]
    fn returns_expected4() {
      assert_eq!(last_digit("10","10000000000"), 0);
    }

    #[test]
    fn returns_expected5() {
      assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
    }

    #[test]
    fn returns_expected6() {
      assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
    }

    #[test]
    fn returns_expected7(){
        assert_eq!(last_digit("0", "0"), 1);
    }

    #[test]
    fn returns_expected8(){
        assert_eq!(last_digit("189", "0"), 1);
    }
}
  