

def main():
    score1 = int(input("Score 1: "))
    score2 = int(input("Score 2: "))
    score3 = int(input("Score 3: "))

    scores(score1)
    scores(score2)
    scores(score3)



def scores(score):
    for i in range(score):
        print("#", end="")
    print()


main()