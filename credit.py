from cs50 import get_int


def main():
    card = get_int("Card number: ")
    checksum(card)  # Check is the card number legit or not


def checksum(card):
    card_num = card
    digit = 0
    checksum = 0

    card_num = int(card_num / 10)

    while True:
        if card_num == 0:
            break
        digit = (card_num % 10) * 2
        card_num = int(card_num / 100)

        if digit > 9:
            digit = int(digit / 10) + digit % 10

        checksum = checksum + digit

    card_num = card

    while True:
        if card_num == 0:
            break
        digit = (card_num % 10)
        card_num = int(card_num / 100)
        checksum = checksum + digit

    if checksum % 10 == 0:
        card_length(card)
    else:
        print("INVALID")


def bank_cards(prefix, length):
    if length in [13, 16] and prefix >= 40 and prefix < 50:
        print("VISA")
    elif length == 16 and prefix >= 51 and prefix <= 55:
        print("MASTERCARD")
    elif length == 15 and (prefix == 34 or prefix == 37):
        print("AMEX")
    else:
        print("INVALID")


def card_length(card):

    card_num = card
    length = 0
    while True:
        if card_num == 0:
            break
        length += 1
        card_num = int(card_num / 10)

    prefix = card
    card = length

    while True:
        if length == 2:
            break

        prefix = int(prefix / 10)
        length = length - 1

    length = card
    bank_cards(prefix, length)


main()