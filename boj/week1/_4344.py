tc = int(input())

for t in range(tc):
    rd = input().split()
    n = int(rd[0])
    sum = 0

    for i in range(1, len(rd)):
        sum += int(rd[i])

    avg = float(sum / n)

    count = 0
    for i in range(1, n + 1):
        if int(rd[i]) > avg:
            count += 1

    print("{:.3f}".format((count / n) * 100) + "%")
