use std::path::Path;
use std::io;
use std::fs;


fn extract_bounds(bounds: &str) -> io::Result<(u64, u64)> {
    let (lower_str, upper_str) = match bounds.split_once('-') {
        Some(parts) => parts,
        None => return Err(io::Error::new(io::ErrorKind::InvalidInput, "Invalid range format")),
    };

    
    let lower_bound: u64 = match lower_str.trim().parse::<u64>() {
        Ok(val) => val,
        Err(_) => return Err(io::Error::new(io::ErrorKind::InvalidInput, "Invalid lower bound format")),
    };

    let upper_bound: u64 = match upper_str.trim().parse::<u64>() {
        Ok(val) => val,
        Err(_) => return Err(io::Error::new(io::ErrorKind::InvalidInput, "Invalid upper bound format"))
    };

    return Ok((lower_bound, upper_bound));
}

/// Function takes the challange input location as paht and returns an array consisting of tuples with two integer values
fn parse_id_bounds(input: &str) -> Vec<(u64, u64)> { // we have a vector of tuples with two u64 values, the vector
    let mut id_ranges: Vec<(u64, u64)> = Vec::new();

    for bound_string in input.split(",") {
        let bound: (u64, u64) = match  extract_bounds(bound_string) {
            Ok(val) => val,
            Err(_) => continue,
        };

        id_ranges.push(bound);
    }

    return id_ranges;
}

/// id checker for first challenge only check if in id consists of two similar parts
fn check_id_range_validity_twice(lower_bound: u64, upper_bound: u64) -> u64 {
    let mut similarity_counter: u64 = 0;

    for i in lower_bound..=upper_bound {
        let id_string: String = i.to_string();

        // an odd length can't consit of two similar parts
        if id_string.len() % 2 != 0 {
            continue;
        }

        // check if the first half is simmilar to the second half, if so then increase the counter
        let id_split: (&str, &str) = id_string.split_at((id_string.len() / 2) as usize);
        similarity_counter += ((id_split.0 == id_split.1) as u64) * i;
    }

    return similarity_counter;
}

/// id checker for second challenge. the return value is the sum of all invalid ids where any given id consists of at least two times the same pattern
/// 
/// Example:
/// 11 => two times 1
/// 111 => three times 1
/// 123412341234 => three times 1234 
fn check_id_range_validity_multiple(lower_bound: u64, upper_bound: u64) -> u64 {
    let mut similarity_counter: u64 = 0;

    for i in lower_bound..=upper_bound {
        let id_string: String = i.to_string();

        for split_pos in 1..=((id_string.len() / 2) as usize) {
            // id_split is a tuple where the first value is the pattern and the second value is the rest of the number where we have to check whether there is a repeating pattern
            let id_split = id_string.split_at(split_pos);
            
            // if the rest of the number is not divisable by the pattern lenght as whole number, then the check can be skipped
            if id_split.1.len() % id_split.0.len() != 0 {
                continue;
            }
            let found_reps: Vec<(usize, &str)> = id_split.1.match_indices(id_split.0).collect();
            if found_reps.len() * id_split.0.len() == id_split.1.len() {
                similarity_counter += i;
                break;
            }
        }

    }

    return similarity_counter;
}

fn one() -> u64 {
    let file_path: &Path = Path::new("data/input.txt");
    let file_content: String = fs::read_to_string(file_path).expect("failed to read input.txt");
    let bounds = parse_id_bounds(&file_content);

    let mut similarity_counter: u64 = 0;
    for bound in bounds {
        similarity_counter += check_id_range_validity_twice(bound.0, bound.1);
    }

    return similarity_counter;
}

fn two() -> u64 {
    let file_path: &Path = Path::new("data/input.txt");
    let file_content: String = fs::read_to_string(file_path).expect("failed to read input.txt");
    let bounds = parse_id_bounds(&file_content);

    let mut similarity_counter: u64 = 0;
    for bound in bounds {
        similarity_counter += check_id_range_validity_multiple(bound.0, bound.1);
    }

    return similarity_counter;
}


fn main() {
    let res_one = one();
    let res_two = two();

    println!("{}", res_one);
    println!("{}", res_two);
}

#[cfg(test)]
mod aoc_day_2_tester {
    use super::*;

    const REF_VALUE_AOC: [(u64, u64); 11] = [
        (11, 22),
        (95, 115),
        (998, 1012),
        (1188511880, 1188511890),
        (222220, 222224),
        (1698522, 1698528),
        (446443, 446449),
        (38593856, 38593862),
        (565653, 565659),
        (824824821, 824824827),
        (2121212118, 2121212124),
    ];


    #[test]
    fn parser_single() {
        let input: &str = "11-22";
        let ref_value: Vec<(u64, u64)> = vec![(11, 22)];
        let parse_output = parse_id_bounds(input);

        assert_eq!(ref_value, parse_output);
    }

    #[test]
    fn parser_multiple() {
        let input: &str = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";
        let parse_output = parse_id_bounds(input);

        assert_eq!(parse_output, REF_VALUE_AOC.to_vec());
    }

    #[test]
    fn id_validity_range() {
        let lower_bound: u64 = 11;
        let upper_bound: u64 = 22;

        let similarity_counter: u64 = check_id_range_validity_twice(lower_bound, upper_bound);

        assert_eq!(similarity_counter, 33);
    }
    
    #[test]
    fn bound_parser() {
        let file_path: &Path = Path::new("data/test.txt");
        let file_content: String = fs::read_to_string(file_path).expect("");
        let bounds = parse_id_bounds(&file_content);

        assert_eq!(bounds, REF_VALUE_AOC.to_vec())
    }

    #[test]
    fn id_validity_aoc_one() {
        let mut similarity_counter: u64 = 0;
        
        for bounds in REF_VALUE_AOC.to_vec() {
            similarity_counter += check_id_range_validity_twice(bounds.0, bounds.1);
        }

        assert_eq!(similarity_counter, 1227775554);
    }

    #[test]
    fn id_validity_aoc_two() {
        let mut similarity_counter: u64 = 0;
        
        for bounds in REF_VALUE_AOC.to_vec() {
            similarity_counter += check_id_range_validity_multiple(bounds.0, bounds.1);
        }

        assert_eq!(similarity_counter, 4174379265);
    }

}
