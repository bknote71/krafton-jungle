arr = input().split()

flag = -1

for i in range(3):
    if arr[0][3 - i - 1] > arr[1][3 - i - 1]:
        flag = 0
        break
    elif arr[0][3 - i + 1] < arr[1][3 - i + 1]:
        flag = 1
        break
if flag == -1:
    flag = 0
print(arr[flag][::-1])
