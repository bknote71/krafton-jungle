import math

arr = input().split()
x = int(arr[0])
y = int(arr[1])
w = int(arr[2])
h = int(arr[3])

minv = 10000000

minv = min(minv, abs(x - 0))
minv = min(minv, abs(y - 0))
minv = min(minv, abs(w - x))
minv = min(minv, abs(y - h))

print(minv)
