rd = input().split()
N = int(rd[0])
X = int(rd[1])

arr = input().split()

for i in arr:
    if X > int(i):
        print(i, end=' ')
