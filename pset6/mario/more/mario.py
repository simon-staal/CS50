from cs50 import get_int

while 1:
    n = get_int("Please input a number between 1 and 8 inclusive: ")
    if n > 0 and n < 9:
        break

for i in range(n):
    print((" " * (n - (i + 1))) + ("#" * (i + 1)) + "  " + ("#" * (i + 1)))