//https://www.codewars.com/kata/57591ef494aba64d14000526
fn john(n: i32) -> Vec<i32> {
    let mut a: Vec<i32> = vec![1];
    let mut j: Vec<i32> = vec![0];
    while j.len() != n as usize{
        if a.len() as i32 > j[j.len()-1]{
            j.push(j.len() as i32 - a[j[j.len()-1] as usize])
        }
        else{
            a.push(a.len() as i32 - j[a[a.len()-1] as usize])
        }
    }
    j
}

fn ann(n: i32) -> Vec<i32> {
    let mut a: Vec<i32> = vec![1];
    let mut j: Vec<i32> = vec![0];
    while a.len() != n as usize{
        if a.len() as i32 > j[j.len()-1]{
            j.push(j.len() as i32 - a[j[j.len()-1] as usize])
        }
        else{
            a.push(a.len() as i32 - j[a[a.len()-1] as usize])
        }
    }
    a
}

fn sum_john(n: i32) -> i32 {
    john(n).iter()
           .sum()
}

fn sum_ann(n: i32) -> i32 {
    ann(n).iter()
          .sum()
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_john1() {
        assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
    }
    #[test]
    fn test_john2() {
        assert_eq!(john(14), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
    }
    #[test]
    fn test_ann1() {
        assert_eq!(ann(6), vec![1, 1, 2, 2, 3, 3]);
    }
    #[test]
    fn test_ann2() {
        assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
    }
    #[test]
    fn test_sum_john1() {
        assert_eq!(sum_john(75), 1720);
    }
    #[test]
    fn test_sum_john2() {
        assert_eq!(sum_john(78), 1861);
    }
    #[test]
    fn test_sum_ann1() {
        assert_eq!(sum_ann(115), 4070);
    }
    #[test]
    fn test_sum_ann2() {
        assert_eq!(sum_ann(150), 6930);
    }
}

