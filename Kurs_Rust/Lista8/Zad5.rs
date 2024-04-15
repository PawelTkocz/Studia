//https://www.codewars.com/kata/5aec1ed7de4c7f3517000079
fn first_n_smallest (arr: &[i32], n: usize) -> Vec<i32> {
    if n == 0{
        return vec![];
    }
    let mut c = arr.iter()
                   .map(|x| *x)
                   .collect::<Vec<i32>>();
    c.sort();
    let mut d = arr.iter()
                   .map(|x| *x)
                   .collect::<Vec<i32>>();
    let maxi = c[n-1];
    d = d.iter()
         .filter(|&x| x <= &maxi)
         .map(|x| *x)
         .collect::<Vec<i32>>();
    d.reverse();
    while d.len() != n{
        let i = d.iter()
                 .position(|x| *x == maxi)
                 .unwrap();
        d.remove(i);
    }
    d.reverse();
    d
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],3), [1,2,3]);
    }
    #[test]
    fn test2() {
        assert_eq!(first_n_smallest(&[5,4,3,2,1],3), [3,2,1]);
    }
    #[test]
    fn test3() {
        assert_eq!(first_n_smallest(&[1,2,3,1,2],3), [1,2,1]);
    }
    #[test]
    fn test4() {
        assert_eq!(first_n_smallest(&[1,2,3,-4,0],3), [1,-4,0]);
    }
    #[test]
    fn test5() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],0), []);
    }
    #[test]
    fn test6() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],5), [1,2,3,4,5]);
    }
    #[test]
    fn test7() {
        assert_eq!(first_n_smallest(&[1,2,3,4,2],4), [1,2,3,2]);
    }
    #[test]
    fn test8() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],2), [2,1]);
    }
    #[test]
    fn test9() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],3), [2,1,2]);
    }
    #[test]
    fn test10() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],4), [2,1,2,2]);
    }
}
