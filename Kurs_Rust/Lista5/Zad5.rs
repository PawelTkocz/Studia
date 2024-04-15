use std::vec;

fn sum_pairs(ints: &[i8], s: i8) -> Option<(i8, i8)> {
    let mut sorted = vec![];
    sorted.push(ints[0]);
    for second in 1..ints.len(){
        if sorted.binary_search(&(s-ints[second])).is_ok(){
            return Some((s-ints[second], ints[second]));
        }
        let ind = sorted.binary_search(&ints[second]);
        if ind.is_err(){
            sorted.insert(ind.err().unwrap(), ints[second]);
        }
    }
    return None
}

fn main() {
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        let l1 = [1, 4, 8, 7, 3, 15];
        assert_eq!(sum_pairs(&l1, 8), Some((1, 7)));
    }    

    #[test]
    fn test2() {
        let l2 = [1, -2, 3, 0, -6, 1];
        assert_eq!(sum_pairs(&l2, -6), Some((0, -6)));
    }    

    #[test]
    fn test3() {
        let l3 = [20, -13, 40];
        assert_eq!(sum_pairs(&l3, -7), None);
    }    

    #[test]
    fn test4() {
        let l4 = [1, 2, 3, 4, 1, 0];
        assert_eq!(sum_pairs(&l4, 2), Some((1, 1)));
    }    

    #[test]
    fn test5() {
        let l5 = [10, 5, 2, 3, 7, 5];
        assert_eq!(sum_pairs(&l5, 10), Some((3, 7)));
    }    

    #[test]
    fn test6() {
        let l6 = [4, -2, 3, 3, 4];
        assert_eq!(sum_pairs(&l6, 8), Some((4, 4)));
    }    

    #[test]
    fn test7() {
        let l7 = [0, 2, 0];
        assert_eq!(sum_pairs(&l7, 0), Some((0, 0)));
    }    

    #[test]
    fn test8() {
        let l8 = [5, 9, 13, -3];
        assert_eq!(sum_pairs(&l8, 10), Some((13, -3)));
    }    
}

