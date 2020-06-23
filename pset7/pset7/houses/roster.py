from sys import argv, exit
import csv
from cs50 import SQL

if len(argv) != 2:
    print('Usage: python roster.py <housename>')
    exit(1)

housename = argv[1]

db = SQL("sqlite:///students.db")

query_results = db.execute('SELECT * FROM students WHERE (house=?) ORDER BY last', housename)

for row in query_results:
    if row['middle'] != None:
        print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')
    else:
        print(f'{row["first"]} {row["last"]}, born {row["birth"]}')