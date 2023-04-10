st = []
N = int(input())


def hanoi(n, s, e, o):
    if n == 1:
        return 1

    x = hanoi(n - 1, s, o, e)
    y = hanoi(n - 1, o, e, s)
    return x + y + 1


def hanoi2(n, s, e, o):
    if n == 1:
        print(s + 1, e + 1)
        return

    hanoi2(n - 1, s, o, e)
    print(s + 1, e + 1)
    hanoi2(n - 1, o, e, s)
    return


print(2**N - 1)
if N <= 20:
    hanoi2(N, 0, 2, 1)
