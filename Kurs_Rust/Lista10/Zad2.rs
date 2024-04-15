//https://www.codewars.com/kata/5552101f47fc5178b1000050
fn dig_pow(n: i64, p: i32) -> i64 {
    let l = n.to_string().len();
    let k = n.to_string()
             .chars()
             .into_iter()
             .map(|x| x.to_digit(10).unwrap())
             .zip((p..p+l as i32).into_iter())
             .map(|(a, b)| (a as u64).pow(b as u32))
             .sum::<u64>() as f64 / n as f64;
    
    if k.fract() == 0.0{
        k as i64
    }
    else{
        -1
    }
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(n: i64, p: i32, exp: i64) -> () {
        println!(" n: {:?};", n);
        println!("p: {:?};", p);
        let ans = dig_pow(n, p);
        println!(" actual:\n{:?};", ans);
        println!("expect:\n{:?};", exp);
        println!(" {};", ans == exp);
        assert_eq!(ans, exp);
        println!("{};", "-");
    }
    
    #[test]
    fn test1() {
        dotest(89, 1, 1);
    }

    #[test]
    fn test2() {
        dotest(92, 1, -1);
    }

    #[test]
    fn test3() {
        dotest(46288, 3, 51);
    }

    #[test]
    fn test4() {
        dotest(695, 2, 2);
    }

    #[test]
    fn test5() {
        dotest(2, 2, 2);
    }
}

