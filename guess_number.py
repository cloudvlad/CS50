import random


def main():
    number = random.randint(1,10)
    while True:
        guess = int(input("Guess the number: "))
        if guess != number:
            advice(guess, number)
        else:
            print("Correct!")
            break



def advice(guess, number):
    if guess > number:
        print("Try a little bit lower!")
    else:
        print("Try a little bit higher!")



main()