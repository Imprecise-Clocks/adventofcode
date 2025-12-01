use std::fs::File;
use std::io::{self, prelude::*};
use std::path::Path;

/// Funtion to move the dial according to the instruction and wraps at 99
/// The instruction is a string that consits of a leading char that determines the direction 
/// L for left or subtraction
/// R for righ or adding
/// the subsequent letters are the number of steps
/// 
/// The dial is wrapped to not overflow 99 or underflow 0, it implements a circular behaviour such that 99 + 1 = 0 and 0 - 1 = 99
fn move_dial(dial: &mut i32, instruction: &str) -> u32 {
    if instruction.len() < 2 {
        eprintln!("step instruction is invalid: {}", instruction);
        return 0;
    }
    
    let first = instruction.chars().next().unwrap();

    let dir: i32 = match first {
        'L' => -1,
        'R' =>  1,
        _   => {
            eprintln!("invalid direction: {}", first);
            return 0;
        }
    };

    let mut steps: i32 = match instruction[1..].parse() {
        Ok(n) => n,
        Err(_) => {
            eprintln!("parsing of steps is invalid: {}", instruction);
            return 0;
        }
    };

    let mut zero_counter: u32 = (steps / 100) as u32;
    steps = (steps % 100) as i32;

    if *dial + dir * steps < 0 {
        if *dial != 0 {
            zero_counter += 1;
        }
        *dial += dir * steps + 100;
    }
    else if *dial + dir * steps > 99 {
        if *dial != 0 {
            zero_counter += 1;
        }
        *dial += dir * steps - 100;
    }
    else {
        *dial += dir * steps;
        
        if *dial == 0 {
            zero_counter += 1;
        }
    }


    return zero_counter;

}

/// Advent of code day one
fn one() -> u32 {
    let mut dial: i32  = 50;
    let mut zero_coutner: u32 = 0;

    if let Ok(lines) = read_lines("data/1.txt") {
        for line in lines.map_while(Result::ok) {
            move_dial(&mut dial, &line);
            if dial == 0 {
                zero_coutner += 1;
            }
        }
    }

    
    // alternative with match statement
    /* match read_lines("../data/1.txt") {
        Ok(lines) => {
            for line in lines.map_while(Result::ok) {
                ...
            }
        }
        Err(_) => {}
    } */


    zero_coutner
}

/// Advent of code day two
fn two()-> u32 {
    let mut dial: i32 = 50;
    let mut zero_counter: u32 = 0;

    if let Ok(lines) = read_lines("data/1.txt") {
        for line in lines.map_while(Result::ok) {
            zero_counter += move_dial(&mut dial, &line) as u32;
        }
    }
    
    zero_counter
}

fn main() {
    let result_one: u32 = one();
    let result_two: u32 = two();

    println!("{}", result_one);
    println!("{}", result_two);
}


fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

#[cfg(test)]
mod tests {
    use super::move_dial;

    #[test]
    fn test_overflow() {
        let mut dial: i32 = 50;
        let instruction: String = "R60".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 10);
        assert_eq!(zero_count, 1);
    }

    #[test]
    fn test_underflow() {
        let mut dial: i32 = 50;
        let instruction: String = "L60".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 90);
        assert_eq!(zero_count, 1);
    }

    #[test]
    fn test_add() {
        let mut dial: i32 = 50;
        let instruction: String = "R20".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 70);
        assert_eq!(zero_count, 0);
    }

    #[test]
    fn test_subtract() {
        let mut dial: i32 = 50;
        let instruction: String = "L20".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 30);
        assert_eq!(zero_count, 0);
    }

    #[test]
    fn test_edge_top() {
        let mut dial: i32 = 50;
        let instruction: String = "R50".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 0);
        assert_eq!(zero_count, 1);
    }

    #[test]
    fn test_edge_bottom() {
        let mut dial: i32 = 50;
        let instruction: String = "L50".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 0);
        assert_eq!(zero_count, 1);
    }

    #[test]
    fn test_overflow_hundred() {
        let mut dial: i32 = 50;
        let instruction: String = "R10000".to_string();
        let zero_count: u32 = move_dial(&mut dial, &instruction);

        assert_eq!(dial, 50);
        assert_eq!(zero_count, 100);
    }

    #[test]
    fn test_aoc_test() {
        let mut dial: i32 = 50;
        let instructions = vec![
            "L68", "L30", "R48", "L5", "R60",
            "L55", "L1", "L99", "R14", "L82",
        ];
        
        let mut zero_count_one: u32 = 0;
        let mut zero_count_two: u32 = 0;
        for instruction in instructions {
            zero_count_two += move_dial(&mut dial, &instruction);
            if dial == 0 {
                zero_count_one += 1;
            }
        }

        assert_eq!(zero_count_one, 3);
        assert_eq!(zero_count_two, 6);
    }

}