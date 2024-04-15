mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        let mut res = vec![];
        let mut last = a[0];
        let mut prev = a[0];
        let mut cnt = 0;

        for i in a{
            if i - 1 <= last {
                cnt += 1;
            }
            else{
                if cnt == 1{
                    res.push(last.to_string());
                }
                else if cnt == 2{
                    res.push(prev.to_string());
                    res.push(last.to_string());
                }
                else{
                    res.push(format!("{}-{}", last-cnt+1, last))
                }
                cnt = 1;
            }
            prev = last;
            last = *i;
        }
        
        if cnt == 1{
            res.push(last.to_string());
        }
        else if cnt == 2{
            res.push(prev.to_string());
            res.push(last.to_string());
        }
        else{
            res.push(format!("{}-{}", last-cnt+1, last))
        }
        res.join(",")
    }
}

fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        assert_eq!(solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]), "-6,-3-1,3-5,7-11,14,15,17-20");	
    }

    #[test]
    fn test2() {
        assert_eq!(solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]), "-3--1,2,10,15,16,18-20");
    }

    #[test]
    fn test3() {
        assert_eq!(solution::range_extraction(&[5]), "5");
    }

    #[test]
    fn test4() {
        assert_eq!(solution::range_extraction(&[2, 3, 5, 6, 9, 10, 12, 13]), "2,3,5,6,9,10,12,13");
    }

    #[test]
    fn test5() {
        assert_eq!(solution::range_extraction(&[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12]), "0-10,12");
    }
}

