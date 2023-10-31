fn get_char(x: i32, y: i32, n: i32) -> String{
    if x == n{
        return "\n".to_string();
    }
    let squares = ["■", "□"];
    let sq0_ind = if (n-1)/2%2 == 0 {0} else {1};
    let sq1_ind = (sq0_ind+1)%2;
    if x%2 == 0 {
        let side = std::cmp::min(x, n-x-1);
        if (y%2==0) || (y>side && y<n-side) {
            squares[sq0_ind].to_string()
        }
        else{
            squares[sq1_ind].to_string()
        }
    }
    else{
        let side = std::cmp::min(x, n-x-1);
        if (y%2==0) && (y<side || y>=n-side) {
            squares[sq0_ind].to_string()
        }
        else{
            squares[sq1_ind].to_string()
        }
    }
}

fn zoom(n: i32) -> String {
    (0..(n+1)*n-1).map(|x| get_char(x%(n+1), x/(n+1), n)).collect()
}

fn main() {
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_test_1() {
        assert_eq!(zoom(1), "■");
    }

    #[test]
    fn basic_test_2() {
        assert_eq!(zoom(3), "□□□\n□■□\n□□□");
    }

    #[test]
    fn basic_test_3() {
        assert_eq!(zoom(5), "■■■■■\n■□□□■\n■□■□■\n■□□□■\n■■■■■");
    }

    #[test]
    fn basic_test_4() {
        assert_eq!(zoom(7), "□□□□□□□\n□■■■■■□\n□■□□□■□\n□■□■□■□\n□■□□□■□\n□■■■■■□\n□□□□□□□");
    }

    #[test]
    fn basic_test_5() {
        assert_eq!(zoom(9), "■■■■■■■■■\n■□□□□□□□■\n■□■■■■■□■\n■□■□□□■□■\n■□■□■□■□■\n■□■□□□■□■\n■□■■■■■□■\n■□□□□□□□■\n■■■■■■■■■");
    }
}
