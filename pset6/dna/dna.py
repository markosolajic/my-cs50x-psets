# Author: Marko Solajic

import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrect number of command-line arguments")
        sys.exit(1)

    # TODO: Read database file into a variable - list of dictionaries
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

        field_names = reader.fieldnames

    # TODO: Read DNA sequence file into a variable - string
    with open(sys.argv[2], "r") as file:
        dna = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    dna_STR_count = []
    for STR in field_names[1:]:
        # DNA STR count in a list
        dna_STR_count.append(longest_match(dna, STR))

    # TODO: Check database for matching profiles
    for person in database:
        # Current person's STR count in a list
        person_STR_count = list(person.values())[1:]
        person_STR_count = [int(STR) for STR in person_STR_count]

        if person_STR_count == dna_STR_count:
            print(person["name"])
            break
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
