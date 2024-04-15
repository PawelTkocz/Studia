//https://www.codewars.com/kata/5868a68ba44cfc763e00008d
fn fill_parenthesis(code: &str) -> Vec<i32>{
    let mut res = vec![2; code.len()];
    let mut left = vec![];
    for i in 0..code.len(){
        if code.as_bytes()[i] == b'['{
            left.push(i);
        }
        else if code.as_bytes()[i] == b']'{
            let left_ind: i32 = *left.last().unwrap() as i32;
            res[i] = left_ind;
            res[left_ind as usize] = i as i32;
            left.pop();
        }
    }
    res
}

fn interpreter(code: &str, iterations: usize, width: usize, height: usize) -> String {
    let mut res = vec![vec!['0'; width]; height];
    let mut x = 0;
    let mut y = 0;
    let mut cnt = 0;
    let mut i = 0;
    let parenthesis = fill_parenthesis(code);
    while i<code.len() && cnt<iterations{
        cnt += 1;
        match code.as_bytes()[i]{
            b'n' =>  y=(y+height-1)%height,
            b'e' =>  x=(x+1)%width,
            b's' =>  y=(y+1)%height,
            b'w' =>  x=(x+width-1)%width,
            b'*' =>  if res[y][x] == '0'{
                        res[y][x] = '1';
                     }
                     else{
                         res[y][x] = '0';
                     },
            b'[' =>  if res[y][x] == '0'{
                        i = parenthesis[i] as usize;
                     },
            b']' =>  if res[y][x] != '0'{
                        i = parenthesis[i] as usize;
                     }
            _    =>  cnt-=1,
        }
        i += 1;
    }
    res.iter()
       .map(|x| x.into_iter()
                 .collect())
       .collect::<Vec<String>>()
       .join("\r\n")
}


fn main() {
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9)), display_expected("000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should initialize all cells in the datagrid to 0");
    }

    #[test]
    fn test2() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9)), display_expected("111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should adhere to the number of iterations specified");
    }

    #[test]
    fn test3() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 19, 6, 9)), display_expected("111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should traverse the 2D datagrid correctly");
    }

    #[test]
    fn test4() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 42, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should traverse the 2D datagrid correctly for all of the \"n\", \"e\", \"s\" and \"w\" commands");
    }

    #[test]
    fn test5() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    }

    #[test]
    fn test6() {
        assert_eq!(display_actual(&interpreter("*[e[*][s][e[*e]*w]n*]", 100, 2, 2)), display_expected("00\r\n01"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    }

    /// Prints representation of datagrid - 0's are black and 1's are white.
    /// Note: it only works properly if your interpreter returns a representation
    /// of the datagrid in the correct format.
    fn pretty_print(datagrid: &str) -> &str {
        let rows = datagrid.split("\r\n");
        let mut output = String::new();
        output += "<pre>";
        for row in rows {
            for cell in row.chars() {
                output += "<span style=\"color:"; 
                output += if cell == '0' { "black" } else { "white" };
                output += ";background-color:"; 
                output += if cell == '0' { "black" } else { "white" };
                output += "\">xx</span>";
            }
            output += "<br />";
        }
        output += "</pre>";
        println!("{}", output);
        datagrid
    }

    /// Displays the grid the interpreter returns
    fn display_actual(actual: &str) -> &str {
        println!("You returned:");
        pretty_print(actual)
    }

    /// Displays the expected final state of datagrid
    fn display_expected(expected: &str) -> &str {
        println!("Expected final state of data grid:");
        pretty_print(expected)
    }   
}