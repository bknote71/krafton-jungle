N = int(input())


def isSorted(n):
    if len(n) == 1:
        return True
    diff = int(n[1]) - int(n[0])

    for i in range(1, len(n) - 1):
        if int(n[i + 1]) - int(n[i]) != diff:
            return False
    return True


count = 0
for i in range(1, N + 1):
    count += 1 if isSorted(str(i)) else 0

print(count)
