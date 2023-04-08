tc = int(input())

for t in range(tc):
    rd = input().split()
    str = []
    for j in range(len(rd[1])):
        for k in range(int(rd[0])):
            print(rd[1][j], end='')
    print('')
