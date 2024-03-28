use std::fs;


fn part1() -> i32
{
    let file: String = fs::read_to_string("input.txt").expect("File not found!");
    let mut floor: i32 = 0;
    for x in file.chars() {
        floor = match x {
            '(' => floor + 1,
            ')' => floor - 1,
            _ => floor,
        }
    }
    floor
}

fn part2() -> i32
{
    let file: String = fs::read_to_string("input.txt").expect("File not found!");
    let mut floor: i32 = 0;
    for (i , x) in file.chars().enumerate() {
        floor = match x {
            '(' => floor + 1,
            ')' => floor - 1,
            _ => floor,
        };
        if floor == -1 {
            return (i + 1) as i32;
        }
    }
    -1
}

fn main() {
    println!("The answer to part one: {}", part1());
    println!("The answer to part two: {}", part2());
}
