score = 0
states = [1, 2, 3]

with open('input.txt', 'r') as f:
    for line in f:
        enemy, response = line.split()


        enemy = int(format(ord(enemy), 'd')) - 64
        response = int(format(ord(response), 'd')) - 87

        if enemy == response: # draw
            score += 3 + response

        elif states[states.index(enemy) - 1] == response: # loose
            score += response
            
        else:
            score += 6 + response

print(score)
