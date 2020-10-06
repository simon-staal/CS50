from sys import exit
from cs50 import get_string

def main():
    text = get_string("Text: ")
    letters = 0
    sentences = 0
    words = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1
        if text[i] == " " or i == len(text)-1:
            words += 1
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            sentences += 1
    L = letters / words * 100
    S = sentences / words * 100
    grade = index(L, S)

    if grade < 1:
        print("Before Grade 1")
        exit(0)
    elif grade > 16:
        print("Grade 16+")
        exit(0)
    else:
        print(f"Grade {grade}");
        exit(0)

def index(L, S):
    return round(0.0588 * L - 0.296 * S - 15.8)

main()