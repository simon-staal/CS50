from sys import argv, exit
import csv
import re

def main():
    # Checks number of command line arguments
    if len(argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        exit(1)

    # Reads contents of csv file
    with open(argv[1], newline='') as f:
        reader = csv.reader(f)
        data = list(reader)

    # Reads contents of txt file
    with open(argv[2], "r") as file:
        sequence = file.read()

    # Creates list containing all DNA codes in the header
    header = (data[0])[1:]
    matches = []

    # Loops through the DNA code finding longest repeating sequence, then adding the numberical value to matches
    for code in header:
        largest = max(re.findall('((?:' + re.escape(code) + ')*)', sequence), key = len)
        occurences = int(len(largest) / len(code))
        matches.append(str(occurences))

    # Loops through database for matching DNA values
    for row in data:
        sub = row[1:]
        if sub == matches:
            print(row[0])
            exit(0)
    print("No match")
    exit(0)


main()