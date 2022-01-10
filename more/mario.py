import cs50


def main():
    while True:
        height = cs50.get_int("Height: ")
        if height <= 8 and height >= 1:
            break

    for row in range(height + 1):
        if row == 0:
            continue

        blank_symbol(height, row)
        hash_symbol(row)

        for i in range(2):
            print(" ", end="")

        hash_symbol(row)

        print("")


def blank_symbol(height, row):
    for i in range(height - row):
        print(" ", end="")


def hash_symbol(row):
    i = 0
    for i in range(row):
        print("#", end="")


main()