N = int(input())
A = [0 for j in range(N)]
B = []

chk = [False for i in range(N)]
maxValue = 0

arr = input().split()

for i in range(N):
    A[i] = int(arr[i])


def permutation(cnt):
    global maxValue
    if cnt == N:
        print(B)
        result = 0
        for i in range(N - 1):
            result += abs(B[i] - B[i + 1])

    for i in range(N):
        if chk[i] == False:
            chk[i] = True
            B.append(A[i])
            permutation(cnt + 1)
            B.pop()
            chk[i] = False


permutation(0)
print(maxValue)
