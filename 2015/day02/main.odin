package day02

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

part_one :: proc() -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Could not open input.txt")
		return -1
	}
	defer delete(data)

	lines, lines_error := strings.split(string(data), "\n")
	if lines_error != nil {
		fmt.println("Could not separate data into lines")
		return -1
	}
	defer delete(lines)
	area := 0
	for line in lines[:len(lines) - 1] {
		dimensisons, dimension_error := strings.split(line, "x")
		if dimension_error != nil {
			fmt.println("Could not seperate line into dimensions")
			return -1
		}
		length, length_ok := strconv.parse_int(dimensisons[0])
		width, width_ok := strconv.parse_int(dimensisons[1])
		height, height_ok := strconv.parse_int(dimensisons[2])
		if !length_ok || !width_ok || !height_ok {
			fmt.println("Error during parsing of one dimension")
			return -1
		}
		area1 := length * width
		area2 := width * height
		area3 := height * length
		area += 2 * (area1 + area2 + area3) + min(area1, area2, area3)
	}
	return area
}

part_two :: proc() -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Could not open input.txt")
		return -1
	}
	defer delete(data)

	lines, lines_error := strings.split(string(data), "\n")
	if lines_error != nil {
		fmt.println("Could not separate data into lines")
		return -1
	}
	defer delete(lines)
	ribbon := 0
	for line in lines[:len(lines) - 1] {
		dimensisons, dimension_error := strings.split(line, "x")
		if dimension_error != nil {
			fmt.println("Could not seperate line into dimensions")
			return -1
		}
		length, length_ok := strconv.parse_int(dimensisons[0])
		width, width_ok := strconv.parse_int(dimensisons[1])
		height, height_ok := strconv.parse_int(dimensisons[2])
		if !length_ok || !width_ok || !height_ok {
			fmt.println("Error during parsing of one dimension")
			return -1
		}
		lh := length + height
		wh := width + height
		lw := length + width
		ribbon += 2 * min(lh, wh, lw) + length * width * height
	}
	return ribbon
}

main :: proc() {
	fmt.println("Result for part one: ", part_one())
	fmt.println("Result for part two: ", part_two())
}
