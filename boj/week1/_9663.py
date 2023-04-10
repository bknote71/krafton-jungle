N = int(input())

pos = []
vst = [False] * N


def canLay(r, c):
    for a, b in pos:
        if r - a == abs(c - b) or b == c:
            return False
    return True


def nqueen(r):
    if r == N:
        return 1

    sum = 0
    for c in range(N):
        if vst[c] == True:
            continue
        if canLay(r, c):
            vst[c] = True
            pos.append((r, c))
            sum += nqueen(r + 1)
            pos.pop()
            vst[c] = False

    return sum


print(nqueen(0))
