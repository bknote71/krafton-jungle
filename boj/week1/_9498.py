N = int(input())
X = ''
if 90 <= N and N <= 100:
    X = 'A'
elif 80 <= N and N <= 89:
    X = 'B'
elif 70 <= N and N <= 79:
    X = 'C'
elif 60 <= N and N <= 69:
    X = 'D'
else:
    X = 'F'

print(X)
