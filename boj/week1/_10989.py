N = int(input())

arr = [0 for i in range(10001)]

for i in range(N):
    x = int(input())
    arr[x] += 1

for i in range(1, 10001):
    for j in range(arr[i]):
        print(i)
