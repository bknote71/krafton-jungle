list = [0 for i in range(10)]

A = int(input())
B = int(input())
C = int(input())

X = str(A*B*C)

for i in range(len(X)):
    list[int(X[i])] = list[int(X[i])] + 1

for i in range(10):
    print(list[i])
