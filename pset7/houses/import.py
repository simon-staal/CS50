import cs50
import csv
from sys import argv
import string

if len(argv) != 2:
    print("Usage: python import.py database.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as students:
    reader = csv.DictReader(students)
    for row in reader:
        name = row["name"]
        names = name.split()
        birth = int(row["birth"])
        if len(names) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, NULL, ?, ?, ?)", names[0], names[1], row["house"], birth)
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", names[0], names[1], names[2], row["house"], birth)


