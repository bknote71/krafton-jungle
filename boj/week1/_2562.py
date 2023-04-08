value = 0
index = -1

for i in range(9):
    x = int(input())
    if x >= value:
        value = x
        index = i

print(value)
print(index + 1)
