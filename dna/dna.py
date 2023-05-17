import csv
import sys


def main():

    # TODO: Check for command-line usage

    n=len(sys.argv)
    if n!=3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)




    # TODO: Read database file into a variable
    name=[]
    dictname={}

    with open(sys.argv[1],"r") as input:
        reader=csv.DictReader(input)

        //Take care here, we will get the header of the csv
        alldna=reader.fieldnames[1:]
        print(alldna)
        for i in range(len(alldna)):
            dictname[alldna[i]]=[]
        for row in reader:
            name.append(row["name"])
            for j in range(len(alldna)):
                dictname[alldna[j]].append(row[alldna[j]])


    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2],"r") as inpu:
        sequen=inpu.readline()

    # TODO: Find longest match of each STR in DNA sequence
    longest=0
    strneed=""
    for i in dictname:
        if longest_match(sequen,i)>longest:
            longest=longest_match(sequen,i)
            strneed=i
            print(longest)
            print(strneed)



    # TODO: Check database for matching profiles
    print(name)
    print(dictname)
    for i in range(len(dictname[strneed])):
        if int(dictname[strneed][i])==longest:
            return name[i]

    return ("Not found.")


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


print(main())
