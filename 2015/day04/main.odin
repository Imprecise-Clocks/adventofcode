package day04

import "core:crypto/legacy/md5"
import "core:encoding/hex"
import "core:fmt"
import "core:os"

has_leading_zeros :: proc(hash: []u8, n: int) -> bool {
	if len(hash) < n {
		return false
	}
	hex_encoded, err := hex.encode(hash[:])
	if err != nil {
		return false
	}
	defer delete(hex_encoded)
	for i in 0 ..< n {
		if hex_encoded[i] != 48 { 	// 48 == 0x0
			return false
		}
	}
	return true
}

solve :: proc(n_leading_zeros: int) -> int {
	data, err := os.read_entire_file("input.txt", context.allocator)
	if err != nil {
		fmt.println("Could not open input.txt")
		return -1
	}
	defer delete(data)
	buffer: [64]u8
	hash: [md5.DIGEST_SIZE]u8
	ctx: md5.Context

	for i := 0;; i += 1 {
		input := fmt.bprintf(buffer[:], "%s%d", data, i)
		md5.init(&ctx)
		md5.update(&ctx, transmute([]u8)input)
		md5.final(&ctx, hash[:])
		if has_leading_zeros(hash[:], n_leading_zeros) {
			return i
		}
	}
}

part_one :: proc() -> int {
	return solve(5)
}

part_two :: proc() -> int {
	return solve(6)
}

main :: proc() {
	fmt.println("Result for part one: ", part_one())
	fmt.println("Result for part two: ", part_two())
}
