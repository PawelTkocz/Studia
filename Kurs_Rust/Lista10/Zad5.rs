//https://www.codewars.com/kata/5503013e34137eeeaa001648
fn print(n: i32) -> Option<String> {
    if n < 0 || n%2==0{
        return None;
    }
    let k = n/2;
    let seq = (k+1..n+1).collect::<Vec<i32>>();
    let seq2 = seq.clone()
                  .into_iter()
                  .rev()
                  .skip(1);
    let rows_len = seq.into_iter()
                      .chain(seq2)
                      .collect::<Vec<i32>>();
    let mut partial_sums = rows_len.iter()
                                    .map(|x| x+1)
                                    .collect::<Vec<i32>>();
    for i in 1..n{
        partial_sums[i as usize] += partial_sums[(i-1) as usize];
    }
    let l = partial_sums[(n-1) as usize];
    let mut res = vec!['\n'; l as usize];
    for i in 0..rows_len[0]{
        if  i < k {
            res[i as usize] = ' ';
        }
        else{
            res[i as usize] = '*';
        }
    }
    let mut cur_row = 1;
    for i in partial_sums[0]..l{
        if i == partial_sums[cur_row]-1{
            cur_row += 1;
            continue;
        }
        if  i < (k-cur_row as i32).abs() + partial_sums[cur_row-1]{
            res[i as usize] = ' ';
        }
        else{
            res[i as usize] = '*';
        }
    }
    return Some(res.iter().collect::<String>())
}

fn main() {
}


#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test1() {
      assert_eq!(print(3), Some(" *\n***\n *\n".to_string()) );
    }

    #[test]
    fn test2() {
      assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()) );
    }

    #[test]
    fn test3() {
      assert_eq!(print(-3),None);
    }

    #[test]
    fn test4() {
      assert_eq!(print(2),None);
    }

    #[test]
    fn test5() {
      assert_eq!(print(0),None);
    }

    #[test]
    fn test6() {
      assert_eq!(print(1), Some("*\n".to_string()) );
    }
}
