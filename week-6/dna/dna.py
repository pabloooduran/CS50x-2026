import csv
import sys


def main():

    # TO DO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Introduce database and sequence as command-line arguments")
        sys.exit(1)
    # TO DO: Read database file into a variable
    rows = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        header = reader.fieldnames
        for row in reader:
            rows.append(row)
    # TO DO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file_2:
        dna_seq = file_2.read()
    # TO DO: Find longest match of each STR in DNA sequence
    dna_longest_repeat = []
    for i in header[1:]:
        dna_longest_repeat.append(longest_match(dna_seq, i))
    # TO DO: Check database for matching profiles
    for i in rows:
        check = 0
        count = 0
        for j in header[1:]:
            if int(i[j]) == dna_longest_repeat[count]:
                check += 1
            count += 1
        if check == len(header) - 1:
            print(i["name"])
            sys.exit(0)

    print("No match")
    sys.exit(0)


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
