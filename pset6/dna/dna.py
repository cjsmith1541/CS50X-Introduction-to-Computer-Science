import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        sys.exit(0)

    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        fieldnames = list(reader.fieldnames)
        for row in reader:
            for name in fieldnames[1:]:
                row[name] = int(row[name])
            data.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequences:
        sequence = sequences.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest_STR = {}
    for i in range(1, len(fieldnames[1:]) + 1):
        longest = longest_match(sequence, fieldnames[i])
        longest_STR[fieldnames[i]] = longest

    # TODO: Check database for matching profiles
    for i in range(len(data)):
        count = 0
        for j in range(len(fieldnames[1:])):
            if data[i][fieldnames[j + 1]] == longest_STR[fieldnames[j + 1]]:
                count += 1
        if count == len(fieldnames[1:]):
            print(data[i]["name"])
            return 1
    print("no match")
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
