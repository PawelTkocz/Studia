fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    if a.len() != b.len(){
        return false;
    }
    let mut a_cpy = a.clone()
                     .iter()
                     .map(|v| v*v)
                     .collect::<Vec<i64>>();
    a_cpy.sort();
    let mut b_cpy = b.clone();
    b_cpy.sort();
    a_cpy.iter()
         .zip(b_cpy)
         .filter(|(&x, y)| x != *y)
         .count() == 0
}

fn main() {
}


#[cfg(test)]
mod tests {
    use super::*;
    fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
        assert_eq!(comp(a, b), exp)
    }
    
    #[test]
    fn test1() {
        let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
        let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
        testing(a1, a2, true);
    }

    #[test]
    fn test2() {
        let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
        let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
        testing(a1, a2, false);  
    }

    #[test]
    fn test3() {
        let a1 = vec![];
        let a2 = vec![];
        testing(a1, a2, true);  
    }

    #[test]
    fn test4() {
        let a1 = vec![];
        let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
        testing(a1, a2, false);  
    }

    #[test]
    fn test5() {
        let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
        let a2 = vec![];
        testing(a1, a2, false);  
    }

    #[test]
    fn test6() {
        let a1 = vec![-5, 5, -8, 9, 0, 3];
        let a2 = vec![0, 9, 25, 25, 81, 64];
        testing(a1, a2, true);  
    }
}

