N = int(input())
A = [0 for j in range(N)]

chk = [False for i in range(N)]

arr = input().split()

for i in range(N):
    A[i] = int(arr[i])


def pair(node, cnt):
    if cnt == (N / 2):
        return 0

    sum = -1

    for mypair in range(node + 1, N):
        if chk[mypair] == False:
            chk[mypair] = True
            nextnode = -1

            for next in range(node + 1, N):
                if chk[next] == False:
                    nextnode = next
                    break
            sum = max(sum, abs(A[node] - A[mypair]) + pair(nextnode, cnt + 1))
            sum = max(sum, abs(A[mypair] - A[node]) + pair(nextnode, cnt + 1))

            chk[mypair] = False
    return sum


chk[0] = True
print(pair(0, 0))
