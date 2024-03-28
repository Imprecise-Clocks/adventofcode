import numpy as np 
import re 

def find_number_sum(line: str, idx: int) -> int:
    cumulative_sum = 0
    slice = line[idx - 1: idx + 2]
    if re.search(r'\d', slice):
        possible_num = slice.split('.')
        running_idx = idx - 1
        if re.match(r'\d', possible_num[0]):
            running_idx = idx - 2
            number = possible_num[0]
            while(re.match(r'\d', line[running_idx])):
                number = line[running_idx] + number
                running_idx -= 1
            running_idx = idx
            while(re.match(r'\d', line[running_idx])):
                number = number + line[running_idx]
                running_idx += 1
            cumulative_sum += int(number)

        if re.match(r'\d', possible_num[1] and running_idx <= idx):
            number = possible_num[1]
            running_idx = idx + 1
            while(re.match(r'\d', line[running_idx])):
                number = number + line[running_idx]
                running_idx += 1
            cumulative_sum += int(number)
        
        elif re.match(r'\d', possible_num[2]):
            number = possible_num[2]
            running_idx = idx + 2
            while(re.match(r'\d', line[running_idx])):
                number = number + line[running_idx]
                running_idx += 1       
            cumulative_sum += int(number)
    return cumulative_sum


def part1() -> int:
    with open("input.txt", mode='r') as file:
        lines = file.readlines()
    
    cumulative_sum = 0
    for row, line in enumerate(lines):
        line = line[:-1]
        for col in re.finditer(r'[^\d\.]', line):
            idx = col.start(0)
            if row != 0:
                cumulative_sum += find_number_sum(lines[row - 1], idx)
            cumulative_sum += find_number_sum(lines[row], idx)
            if row != len(lines) - 1:
                cumulative_sum += find_number_sum(lines[row + 1], idx)

    return cumulative_sum

def part2():
    with open("input.txt", mode='r') as file:
        lines = file.readlines()

    return 0



if __name__ == '__main__':
    print(f"Answer Part 1: {part1()}")
    print(f"Answer Part 2: {part2()}")