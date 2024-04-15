struct Sudoku{
    data: Vec<Vec<u32>>,
}

impl Sudoku{
    
    fn list_valid(l: &Vec<u32>) -> bool{
        let mut l_sort = l.clone();
        l_sort.sort();
        (1..l.len() as u32 +1).collect::<Vec<u32>>()
                              .iter()
                              .zip(l_sort.iter())
                              .filter(|&(a, b)| a != b)
                              .count() == 0
    }

    fn columns_valid(&self) -> bool{
        let n = self.data.len();
        let mut v = vec![0; n];
        for i in 0..n{
            for j in 0..n{
                v[j] = self.data[i][j];
            }
            if !Sudoku::list_valid(&v){
                return false;
            }
        }
        true
    }

    fn rows_valid(&self) -> bool{
        self.data
            .iter()
            .filter(|&v| !Sudoku::list_valid(v)).count() == 0
    }

    fn squares_valid(&self) -> bool{
        let n = self.data.len();
        let mut v = vec![0; n];
        let n_sqrt = (n as f64).sqrt().round() as usize;
        for y in 0..n_sqrt as usize{
            for x in 0..n_sqrt as usize{
                for i in 0..n_sqrt as usize{
                    for j in 0..n_sqrt as usize{
                        v[n_sqrt*i+j] = self.data[n_sqrt*y+i][n_sqrt*x+j];
                    }
                }
                if !Sudoku::list_valid(&v){
                    return false;
                }   
            }
        }
        true
    }

    fn size_valid(&self) -> bool{
        let s = self.data.len();
        if (s as f64).sqrt().fract() != 0.0{
            return false;
        }

        self.data
            .iter()
            .filter(|&v| v.len() == s)
            .count() == s

    }

    fn is_valid(&self) -> bool {
        self.size_valid() && 
        self.columns_valid() && 
        self.rows_valid() && 
        self.squares_valid()
    }
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        let s = Sudoku{
            data: vec![
                    vec![7,8,4, 1,5,9, 3,2,6],
                    vec![5,3,9, 6,7,2, 8,4,1],
                    vec![6,1,2, 4,3,8, 7,5,9],

                    vec![9,2,8, 7,1,5, 4,6,3],
                    vec![3,5,7, 8,4,6, 1,9,2],
                    vec![4,6,1, 9,2,3, 5,8,7],
                    
                    vec![8,7,6, 3,9,4, 2,1,5],
                    vec![2,4,3, 5,6,1, 9,7,8],
                    vec![1,9,5, 2,8,7, 6,3,4]
                ]
        };
        assert!(s.is_valid());
    }

    #[test]
    fn test2() {        
        let s = Sudoku{
            data: vec![
                    vec![1, 4,  2, 3],
                    vec![3, 2,  4, 1],
            
                    vec![4, 1,  3, 2],
                    vec![2, 3,  1, 4],
                ]
        };
        assert!(s.is_valid());
    }

    #[test]
    fn test3() {
        let s = Sudoku{
            data: vec![
                    vec![1,2,3, 4,5,6, 7,8,9],
                    vec![1,2,3, 4,5,6, 7,8,9],
                    vec![1,2,3, 4,5,6, 7,8,9],

                    vec![1,2,3, 4,5,6, 7,8,9],
                    vec![1,2,3, 4,5,6, 7,8,9],
                    vec![1,2,3, 4,5,6, 7,8,9],
                    
                    vec![1,2,3, 4,5,6, 7,8,9],
                    vec![1,2,3, 4,5,6, 7,8,9],
                    vec![1,2,3, 4,5,6, 7,8,9],
                ]
        };
        assert!(!s.is_valid());
    }

    #[test]
    fn test4() {        
        let s = Sudoku{
            data: vec![
                    vec![1,2,3,4,5],
                    vec![1,2,3,4],
                    vec![1,2,3,4],
                    vec![1],
                ]
        };
        assert!(!s.is_valid());
    }

    #[test]
    fn test5() {        
        let s = Sudoku{
            data: vec![
                    vec![1],
                ]
        };
        assert!(s.is_valid());
    }
}


