tc = int(input())

for t in range(tc):
    w = 0
    sum = 0
    str = input()
    for c in range(len(str)):
        if str[c] == 'O':
            w += 1
            sum += w
        else:
            w = 0

    print(sum)
