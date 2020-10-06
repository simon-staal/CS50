from sys import exit
from cs50 import get_int
import re

def main():
    card = get_int("Number: ")
    length = len(str(card))
    if length != 13 and length != 15 and length != 16:
        print("INVALID")
        exit(0)

    if invalid(card):
        print("INVALID")
        exit(0)
    card = str(card)

    if length == 15:
        if re.search("^34", card) or re.search("^37", card):
            print("AMEX")
            exit(0)
        else:
            print("INVALID")
            exit(0)

    if length == 13:
        if re.search("^4", card):
            print("VISA")
            exit(0)
        else:
            print("INVALID")
            exit(0)

    if length == 16:
        if re.search("^4", card):
            print("VISA")
            exit(0)
        for i in range(5):
            if re.search(f"^5{i+1}", card):
                print("MASTERCARD")
                exit(0)
        print("INVALID")
        exit(0)

    print("ERROR")
    exit(1)

def invalid(card):
    card = str(card)
    s = 0
    n = len(card);
    tmp = 0
    for i in card:
        if n % 2:
            s += int(i)
        else:
            tmp = int(i) * 2
            for j in str(tmp):
                s += int(j)
        n -= 1
    if s % 10 == 0:
        return False
    else:
        return True

main()