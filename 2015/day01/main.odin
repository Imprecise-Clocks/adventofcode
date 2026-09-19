package day01

import "core:fmt"
import "core:os"

DIRECTION :: enum {
	UP   = '(',
	DOWN = ')',
}

part_one :: proc() -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Error reading the file")
		return -1
	}
	floor := 0
	for d in data {
		if DIRECTION(d) == DIRECTION.UP {
			floor += 1
		} else if DIRECTION(d) == DIRECTION.DOWN {
			floor -= 1
		}
	}
	return floor
}

part_two :: proc() -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Error reading the file")
		return -1
	}
	floor := 0
	index := 0
	for d in data {
		if DIRECTION(d) == DIRECTION.UP {
			floor += 1
		} else if DIRECTION(d) == DIRECTION.DOWN {
			floor -= 1
		}
		if floor == -1 {
			break
		}
		index += 1
	}
	return index
}

main :: proc() {
	fmt.println("The result for Part One: ", part_one())
	fmt.println("The result for Part Two: ", part_two())

}
