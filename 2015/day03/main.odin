package day02

import "core:fmt"
import "core:os"
import "core:slice"

DIRECTION :: enum {
	UP    = '^',
	DOWN  = 'v',
	LEFT  = '<',
	RIGHT = '>',
}

Coord :: struct {
	x: int,
	y: int,
}

part_one :: proc() -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Could not open input.txt")
		return -1
	}
	defer delete(data)

	world := make(map[Coord]int)
	defer delete(world)
	position: Coord = {0, 0}
	world[position] = 1
	for d in data[:len(data) - 1] {
		switch DIRECTION(d) {
		case .UP:
			position.y += 1
		case .DOWN:
			position.y -= 1
		case .LEFT:
			position.x -= 1
		case .RIGHT:
			position.x += 1
		case:
			fmt.println("Something went wrong", rune(d))
		}
		world[position] = 1
	}
	return len(world)
}

part_two :: proc() -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Could not open input.txt")
		return -1
	}
	defer delete(data)

	world := make(map[Coord]int)
	robo_world := make(map[Coord]int)
	defer delete(world)
	position: Coord = {0, 0}
	robo_position: Coord = {0, 0}
	world[position] = 1
	for d, i in data[:len(data) - 1] {
		is_robo := i % 2 == 1
		switch DIRECTION(d) {
		case .UP:
			position.y += 1 * int(!is_robo)
			robo_position.y += 1 * int(is_robo)
		case .DOWN:
			position.y -= 1 * int(!is_robo)
			robo_position.y -= 1 * int(is_robo)
		case .LEFT:
			position.x -= 1 * int(!is_robo)
			robo_position.x -= 1 * int(is_robo)
		case .RIGHT:
			position.x += 1 * int(!is_robo)
			robo_position.x += 1 * int(is_robo)
		case:
			fmt.println("Something went wrong", rune(d))
		}
		world[position] = 1
		robo_world[robo_position] = 1
	}
	houses := make([dynamic]Coord)
	defer delete(houses)
	for house in world {
		append(&houses, house)
	}
	for house in robo_world {
		if !slice.contains(houses[:], house) {
			append(&houses, house)
		}
	}
	return len(houses)
}

main :: proc() {
	fmt.println("Result for part one: ", part_one())
	fmt.println("Result for part two: ", part_two())
}
