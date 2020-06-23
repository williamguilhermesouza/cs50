from sys import argv, exit
import csv
from cs50 import SQL

if len(argv) != 2:
    print('Usage: python import.py <char.csv>')
    exit(1)

csv_file = argv[1]

db = SQL("sqlite:///students.db")

with open(csv_file, 'r') as inputfile:
    csvreader = csv.reader(inputfile)
    for row in csvreader:
        if row[0] == 'name':
            continue
        names = ['', '', '']
        count = 0
        for ch in row[0]:
            if ch == ' ':
                count += 1
            else:
                names[count] += ch

        if names[2] == '':
            names[1], names[2] = None, names[1]

        db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)',
                (names[0], names[1], names[2], row[1], row[2]))
