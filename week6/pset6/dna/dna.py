import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python FILENAME FILENAME")

    data = list()
    sequence = None
    count = dict()

    # TODO: Read database file into a variable
    with open(sys.argv[1]) as fhand:
        reader = csv.reader(fhand)
        heading = next(reader)
        for row in reader:
            record = dict()
            for i in range(len(row)):
                if i > 0:
                    record[heading[i]] = int(row[i])
                else:
                    record[heading[i]] = row[i]
            data.append(record)

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2]) as fhand:
        sequence = fhand.read()

    # TODO: Find longest match of each STR in DNA sequence

    for i in range(1, len(heading)):
        count[heading[i]] = longest_match(sequence, heading[i])

    # TODO: Check database for matching profiles

    for item in data:
        sharedKeys = set(count.keys()).intersection(item.keys())
        isMatched = True

        for key in sharedKeys:
            if item[key] != count[key]:
                isMatched = False
                break

        if isMatched:
            print(item.get('name'))
            return
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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
