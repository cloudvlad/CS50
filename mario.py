


def main():
    n = int(input("Insert n: "))

    for i in range(1, n + 1, 1):
        blank(n - i)
        brick(i)
        print("")


def blank(n):
    for i in range(n):
        print(" ", end='')

def brick(n):
    for i in range(n):
        print("#", end='')

main()