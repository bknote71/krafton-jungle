N = int(input())
W = [[0 for j in range(N + 1)] for i in range(N + 1)]

vst = [False for i in range(N + 1)]


def travel(currentnode, cnt):
    if cnt == N - 1:
        if W[currentnode][0] != 0:
            return W[currentnode][0]
        else:
            return 1000000000

    sum = 1000000000
    for nextnode in range(N):
        if nextnode != currentnode and vst[nextnode] == False and W[currentnode][nextnode] != 0:
            vst[nextnode] = True
            sum = min(sum, W[currentnode][nextnode] +
                      travel(nextnode, cnt + 1))
            vst[nextnode] = False

    return sum


for i in range(N):
    arr = input().split()
    for j in range(N):
        W[i][j] = int(arr[j])

vst[0] = True
print(int(travel(0, 0)))
