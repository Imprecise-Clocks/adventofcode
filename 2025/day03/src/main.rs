use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn read_lines<P>(filename: P) -> io::Result<io::Lines<BufReader<File>>>
where
    P: AsRef<std::path::Path>,
{
    let file = File::open(filename)?;
    return Ok(BufReader::new(file).lines());
}

fn get_joltage(bank: &str, batteries: usize) -> u64 {
    let mut joltage: Vec<u64> = vec![0; batteries];
    for i in 0..bank.len() {
        for j in 0..batteries {
            if i + j < bank.len() && i + batteries - 1 < bank.len() {
                let digit = (bank.as_bytes()[i + j] - b'0') as u64;
                if digit > joltage[j] {
                    joltage[j] = digit;
                    for k in (j + 1)..batteries {
                        joltage[k] = (bank.as_bytes()[i + k] - b'0') as u64;
                    }
                    break;
                }
            }
        }
    }
    return joltage
        .into_iter()
        .enumerate()
        .map(|(i, x)| x * 10u64.pow((batteries - i - 1) as u32))
        .sum();
}

fn part_one(input_file: &str) -> u64 {
    let mut total_joltage: u64 = 0;
    if let Ok(banks) = read_lines(input_file) {
        for bank in banks.map_while(Result::ok) {
            total_joltage += get_joltage(&bank, 2);
        }
    } else {
        println!("File was not properly opened.");
    }
    return total_joltage;
}

fn part_two(input_file: &str) -> u64 {
    let mut total_joltage: u64 = 0;
    if let Ok(banks) = read_lines(input_file) {
        for bank in banks.map_while(Result::ok) {
            total_joltage += get_joltage(&bank, 12);
        }
    } else {
        println!("File was not properly opened.");
    }
    return total_joltage;
}

fn main() {
    println!("Part One: {}", part_one("src/input.txt"));
    println!("Part Two: {}", part_two("src/input.txt"));
}

#[cfg(test)]
mod tests {
    use crate::get_joltage;

    #[test]
    fn test_case1() {
        let bank: String = "987654321111111".to_string();
        assert_eq!(98, get_joltage(&bank, 2));
    }
    #[test]
    fn test_case2() {
        let bank: String = "811111111111119".to_string();
        assert_eq!(89, get_joltage(&bank, 2));
    }
    #[test]
    fn test_case3() {
        let bank: String = "234234234234278".to_string();
        assert_eq!(78, get_joltage(&bank, 2));
    }
    #[test]
    fn test_case4() {
        let bank: String = "818181911112111".to_string();
        assert_eq!(92, get_joltage(&bank, 2));
    }
    #[test]
    fn test_case5() {
        let bank: String = "987654321111111".to_string();
        assert_eq!(987654321111, get_joltage(&bank, 12));
    }
    #[test]
    fn test_case6() {
        let bank: String = "811111111111119".to_string();
        assert_eq!(811111111119, get_joltage(&bank, 12));
    }
    #[test]
    fn test_case7() {
        let bank: String = "234234234234278".to_string();
        assert_eq!(434234234278, get_joltage(&bank, 12));
    }
    #[test]
    fn test_case8() {
        let bank: String = "818181911112111".to_string();
        assert_eq!(888911112111, get_joltage(&bank, 12));
    }
}
