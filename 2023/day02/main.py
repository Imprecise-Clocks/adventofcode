import numpy as np 

def get_cubes(game: str) -> np.array:
    sets = game.split(';')
    result = []
    for _set in sets:
        cubes = _set.split(',')
        n_red = 0
        n_green = 0 
        n_blue = 0
        for cube in cubes:
            n_red += int(cube.split()[0]) if cube.split()[1] == 'red' else 0
            n_green += int(cube.split()[0]) if cube.split()[1] == 'green' else 0 
            n_blue += int(cube.split()[0]) if cube.split()[1] == 'blue' else 0
        result.append((n_red, n_green, n_blue))
    return np.array(result).transpose()

def part1() -> int:
    with open("input.txt", mode='r') as file:
        lines = file.readlines()
    cumulative_sum = 0
    for line in lines:
        game_id, game = line.split(':')
        game_id = int(game_id.split()[1])

        n_red, n_green, n_blue = get_cubes(game)
        if np.less_equal(n_red, 12).all() and np.less_equal(n_green, 13).all() and np.less_equal(n_blue, 14).all():
            cumulative_sum += game_id

    return cumulative_sum

def part2():
    with open("input.txt", mode='r') as file:
        lines = file.readlines()
    cumulative_sum = 0
    for line in lines:
        game_id, game = line.split(':')
        game_id = int(game_id.split()[1])

        n_red, n_green, n_blue = get_cubes(game)
        min_red = np.max(n_red)
        min_green = np.max(n_green)
        min_blue = np.max(n_blue)

        cumulative_sum += min_blue * min_green * min_red
    return cumulative_sum



if __name__ == '__main__':
    print(f"Answer Part 1: {part1()}")
    print(f"Answer Part 2: {part2()}")