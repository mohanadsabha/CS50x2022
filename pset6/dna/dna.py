import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # TODO: Read database file into a variable
    csv_file = open(sys.argv[1], 'r')
    strands = []
    persons = {}

    for index, row in enumerate(csv_file):
        if index == 0:
            strands = [strand for strand in row.strip().split(',')[1:]]
        else:
            curr_row = row.strip().split(',')
            persons[curr_row[0]] = [int(x) for x in curr_row[1:]]

    # TODO: Read DNA sequence file into a variable
    dna_s = open(sys.argv[2], 'r').read()

    # TODO: Find longest match of each STR in DNA sequence
    final_strand = []
    for i in range(len(strands)):
        max_strand = longest_match(dna_s, strands[i])
        final_strand.append(max_strand)

    # TODO: Check database for matching profiles
    for name, data in persons.items():
        if final_strand == data:
            print(name)
            exit(0)
    else:
        print('No match')
        
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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()