



def main():
    change = float(input("Insert amaount of change: "))

    if not(isinstance(change, float)):
        print("Invalid change!")
        return 2

    if change < 0:
        print("Invalid change!")
        return 1

    c = change * 100

    coining(c)


def coining(coins):
    #quarters (25¢)
    #dimes (10¢)
    #nickels (5¢)
    #pennies (1¢)

    q = 25
    d = 10
    n = 5
    p = 1

    c = 0

    while True:
        if coins == 0:
            print(f"Number of coins {c}")
            break

        if ((coins - q) >= 0):
            coins = coins - q
            c = c + 1
            continue

        if ((coins - d) >= 0):
            coins = coins - d
            c = c + 1
            continue

        if ((coins - n) >= 0):
            coins = coins - n
            c = c + 1
            continue

        if ((coins - p) >= 0):
            coins = coins - p
            c = c + 1
            continue

main()