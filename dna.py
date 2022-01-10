import sys
import csv


def main():
    if len(sys.argv) != 3:
        print("Invalid number of arguments")
        quit()

    # Load the database
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        database = list(reader)

    # Extracts the STRs
    strs = list(database[0].keys())
    strs.pop(0)

    # print(strs, end="\n")

    # Convert strings to integers
    for row in database:
        for s in strs:
            row[s] = int(row[s])

    # Load in the memory the sample
    sample = (open(sys.argv[2], 'r')).read()

    analise = analiser(sample, strs)

    # Search for a  match in the database
    search_database(database, strs, analise)

# Marks and appends all entries to a list with the index of the starting character


def analiser(sample, strs):
    analise = {}

    for s in strs:
        analise[s] = 0

    for s in strs:
        last_index = 0
        entry = []
        while True:
            p = int(sample.find(s, last_index))
            if p < 0:
                entry.append(p)
                analise[s] = find_max_entry(entry, len(s))
                break
            else:
                entry.append(p)
                last_index = p + len(s)  # Change the strating range (last_index) by the lengts of the STR

    return analise


def find_max_entry(entry, size):
    max_entry = 0
    temp_entry = 0
    # If there is only one value (the negative ending of the STR type entries),
    # returns 0 as there are no entries for the STR type
    if(len(entry) == 1):
        return 0

    # Check every entry
    for i in range(0, len(entry)):
        # If the next item is not an entry, but end (negative value) ...
        if entry[i+1] < 0:
            # ...if the previous entry is next to this:
            if entry[i-1] == entry[i] - size:
                temp_entry += 1\
                    # ...if they are not next to each other:
            else:
                temp_entry = 1
            # If the previous max contigious counter is smaller then the new contigious counter
            # make the max counter equal to the temporary (new) counter
            if max_entry < temp_entry:
                max_entry = temp_entry
            # Return the max counter, because there are no more entries
            return max_entry
        # If the previous entry is next to the new
        if entry[i-1] == entry[i] - size:
            temp_entry += 1
            if max_entry < temp_entry:
                max_entry = temp_entry
        # Reset the
        else:
            temp_entry = 1

    return max_entry

# Search all records of the database for every STR


def search_database(database, strs, analise):
    flag = 1
    for record in database:
        for s in strs:
            if analise[s] == record[s]:
                flag = 1
                continue
            else:
                flag = 0
                break
        # If after every STR check there is already a match, exits early
        if flag == 1:
            print(record['name'])
            return

    if flag == 0:
        print("No match")


if __name__ == '__main__':
    main()