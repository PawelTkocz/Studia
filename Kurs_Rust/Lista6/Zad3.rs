//https://www.codewars.com/kata/526d84b98f428f14a60008da
use std::cmp::min;

fn find_min(v: &mut Vec<u64>, mini: u64, d: u64) -> u64 {
    while v[0]*d <= mini {
        v.remove(0);
    }
    v[0]*d
}

fn hamming(n: usize) -> u64 {
    let mut two: Vec<u64> = vec![1];
    let mut three: Vec<u64> = vec![1];
    let mut five: Vec<u64> = vec![1];
    let mut mini = 1;
    for _i in 0..n-1{
        let r = find_min(&mut two, mini, 2);
        let p = find_min(&mut three, mini, 3);
        let d = find_min(&mut five, mini, 5);
        mini = min(min(r, p), d);
        two.push(mini);
        three.push(mini);
        five.push(mini);
    }
    mini
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::hamming;

    #[test]
    fn test1() {
        assert_eq!(hamming(1), 1);
    }

    #[test]
    fn test2() {
        assert_eq!(hamming(4), 4);
    }

    #[test]
    fn test3() {
        assert_eq!(hamming(10), 12);
    }

    #[test]
    fn test4() {
        assert_eq!(hamming(16), 25);
    }

    #[test]
    fn test5() {
        assert_eq!(hamming(19), 32);
    }

    #[test]
    fn test6() {
        assert_eq!(hamming(2), 2);
    }

    #[test]
    fn test7() {
        assert_eq!(hamming(3), 3);
    }
}