//https://www.codewars.com/kata/roboscript-number-2-implement-the-rs1-specification
use std::{ops::Rem, cmp::{min, max}};

#[derive(PartialEq, Debug, Clone, Copy)]
pub enum Direction {
    Up,
    Right,
    Down,
    Left
}

pub fn check_if_maxes(maxes: (i64, i64, i64, i64), pos: (i64, i64)) -> (i64, i64, i64, i64){
    (max(maxes.0, pos.1), max(maxes.1, pos.0), min(maxes.2, pos.1), min(maxes.3, pos.0))
}

pub fn make_op(op: (char, i64), pos: (i64, i64), dir: Direction) -> ((i64, i64), Direction){
    let directions = vec![Direction::Up, Direction::Right, Direction::Down, Direction::Left];
    match op.0{
        'L' => {
            let ind: i64 = directions.iter()
                                     .position(|&d| d == dir)
                                     .unwrap() as i64;
            (pos, directions[(ind-op.1).rem_euclid(4) as usize])
        }
        'R' => {
            let ind: i64 = directions.iter()
                                     .position(|&d| d == dir)
                                     .unwrap() as i64;
            (pos, directions[(ind+op.1).rem(4) as usize])
        }
        _ => {
            match dir{
                Direction::Down => ((pos.0, pos.1-op.1), dir),
                Direction::Right => ((pos.0+op.1, pos.1), dir),
                Direction::Up => ((pos.0, pos.1+op.1), dir),
                Direction::Left => ((pos.0-op.1, pos.1), dir),
            }
        }
    }
}

pub fn draw_line(pos1: (i64, i64), pos2: (i64, i64), res: &mut Vec<Vec<char>>, start: (i64, i64)){
    if pos1.0 == pos2.0{
        let mini = min(pos1.1, pos2.1);
        let maxi = max(pos1.1, pos2.1);
        for i in 0..(maxi-mini+1){
            res[(mini + i - start.1) as usize][(pos1.0 - start.0) as usize] = '*';
        }
    }
    else{
        let mini = min(pos1.0, pos2.0);
        let maxi = max(pos1.0, pos2.0);
        for i in 0..(maxi-mini+1){
            res[(pos1.1 - start.1) as usize][(mini + i - start.0) as usize] = '*';
        }
    }
}

pub fn process_code(codeq: &str, res: &mut Vec<Vec<char>>, start: (i64, i64), draw: bool) -> (i64, i64, i64, i64){
    let mut chars = codeq.chars();
    let mut num:Vec<char> = vec![];
    let mut op: char = chars.next().unwrap();
    let mut cur_pos = (0, 0);
    let mut cur_dir = Direction::Right;
    let mut maxes = (0, 0, 0, 0);

    for c in chars{
        if c.is_digit(10){
            num.push(c);
        }
        else{
            if num.is_empty(){
                num.push('1');
            }
            let out =  make_op((op, num.iter()
                                       .collect::<String>()
                                       .parse::<i64>()
                                       .unwrap()), cur_pos, cur_dir);
            if op == 'F' && draw{
                draw_line(cur_pos, out.0, res, start);
            }
            cur_pos = out.0;
            cur_dir = out.1;
            maxes = check_if_maxes(maxes, cur_pos);
            op = c;
            num.clear();
        }
    }
    if num.is_empty(){
        num.push('1');
    }
    let out = make_op((op, num.iter()
                              .collect::<String>()
                              .parse::<i64>()
                              .unwrap()), cur_pos, cur_dir);
    if op == 'F' && draw{
        draw_line(cur_pos, out.0, res, start);
    }
    cur_pos = out.0; 
    maxes = check_if_maxes(maxes, cur_pos);
    maxes
}

pub fn execute(codeq: &str) -> String {
    if codeq.len() == 0{
        return "*".to_string();
    }
    let maxes = process_code(codeq, &mut vec![vec![]], (0, 0), false);
    let mut res = vec![vec![' '; (maxes.1-maxes.3+1) as usize]; (maxes.0-maxes.2+1) as usize];
    process_code(codeq, &mut res, (maxes.3, maxes.2), true);
    res.iter()
       .map(|v| v.iter()
                 .collect::<String>())
       .collect::<Vec<String>>()
       .into_iter()
       .rev()
       .collect::<Vec<String>>()
       .join("\r\n")
}

fn main() {
}

#[cfg(test)]
macro_rules! expect_equal {
  ($actual:expr, $expected:expr $(,)*) => {{
    let actual = $actual;
    let expected = $expected;
    assert_eq!(actual, expected, "\ngot:\n{}\n\nexpected:\n{}\n", actual, expected);
  }};
}

#[cfg(test)]
mod tests {
    use super::execute;
    
    #[test]
    fn test1() {
        expect_equal!(execute(""), "*");
    }

    #[test]
    fn test2() {
        expect_equal!(execute("FFFFF"), "******");
    }

    #[test]
    fn test3() {
        expect_equal!(
            execute("FFFFFLFFFFFLFFFFFLFFFFFL"),
            "******\r\n*    *\r\n*    *\r\n*    *\r\n*    *\r\n******",
        );
    }

    #[test]
    fn test4() {
        expect_equal!(
            execute("LFFFFFRFFFRFFFRFFFFFFF"),
            "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
        );
    }

    #[test]
    fn test5() {
        expect_equal!(
            execute("LF5RF3RF3RF7"),
            "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
        );
    }
}
