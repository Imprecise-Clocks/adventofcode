use std::fs;

fn part1() -> i32 {
    let file: String = fs::read_to_string("input.txt").expect("File not found!");
    let mut area: i32 = 0;
    for line in file.lines() {
        let dimensions = line.split("x").map(|x| x.parse().unwrap()).collect();
        let [l, w, h] = dimensions;
        area += 2 * l * w + 2 * w * h + 2 * l * h;
    }
    area
}

fn part2() -> i32 {
    -1
}

fn main() {
    println!("The answer to part one: {}", part1());
    println!("The answer to part two: {}", part2());
}
