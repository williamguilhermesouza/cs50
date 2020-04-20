from sys import argv, exit
import csv

if len(argv) != 3:
    print('Invalid params')
    exit(1)

# using variables to store filenames
individuals_csv = argv[1]
sequence_file = argv[2]
individuals = list()

# reading the dna STR data
with open(individuals_csv, 'r') as file:
    csv_reader = csv.DictReader(file)
    counter = 0
    for row in csv_reader:
        individuals.append(row)

# creating a list of the STRs for comparison
STR = list()
STR_counter = list()

for ind in individuals[0]:
    STR.append(ind)
    STR_counter.append(0)

STR.pop(0)
STR_counter.pop(0)

# comparing STR to DNA sequence file
with open(sequence_file, 'r') as file:

    STR_temp_counter = list()

    for count in STR:
        STR_temp_counter.append(0)

    dna = file.readline()

    for char in range(len(dna)):
        for index, seq in enumerate(STR):

            dna_index = char
            while dna[dna_index:dna_index + len(seq)] == seq:

                STR_temp_counter[index] += 1

                if dna_index + len(seq) > len(dna):
                    break
                dna_index += len(seq)

            for index, val in enumerate(STR_temp_counter):
                if val > STR_counter[index]:
                    STR_counter[index] = val
                STR_temp_counter[index] = 0

for ind in individuals:
    match = True
    for index in range(len(STR_counter)):
        if int(ind[STR[index]]) != STR_counter[index]:
            match = False

    if match:
        print(ind['name'])
        exit(0)
    else:
        match = True

print('No match')