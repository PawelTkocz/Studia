fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    array.clone().
          into_iter().
          rev().
          filter(|&x| x%2==0).
          take(number).into_iter().
          collect::<Vec<i32>>().
          into_iter().
          rev().
          collect::<Vec<i32>>()
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_test1() {
        assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
    }   

    #[test]
    fn sample_test2() {
        assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
    }   

    #[test]
    fn sample_test3() {
        assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
    }   

    #[test]
    fn sample_test4() {
        assert_eq!(even_numbers(&vec!(14, 18), 2), vec!(14, 18));
    }   

    #[test]
    fn sample_test5() {
        assert_eq!(even_numbers(&vec!(2), 1), vec!(2));
    }   
}