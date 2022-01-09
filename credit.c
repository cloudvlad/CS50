#include <stdio.h>
#include <cs50.h>

void checksum(unsigned long card);
void card_length(unsigned long card);
void bank_cards(unsigned long prefix, int length);

int main()
{
    unsigned long card;
    card = get_long("Card number: ");

    checksum(card);//Check is the card number legit or not
}


// Calculate the checksum
void checksum(unsigned long card)
{
    unsigned long card_num = card;
    int digit = 0, checksum = 0;
    card_num = card_num / 10;

    while (card_num != 0)
    {
        digit = (card_num % 10) * 2;
        card_num = card_num / 100;
        if (digit > 9)
        {
            digit = (int)digit / 10 + digit % 10;
        }
        checksum = checksum + digit;
    }

    card_num = card;

    while (card_num != 0)
    {
        digit = (card_num % 10);
        card_num = card_num / 100;
        checksum = checksum + digit;
    }

    // If the checksum is correct
    if (checksum % 10 == 0)
    {
        card_length(card);
    }
    else
    {
        printf("INVALID\n");
    }
}


// Consider card length
void card_length(unsigned long card)
{
    unsigned long card_num = card;
    int length = 0;

    // Count the length of the card number
    while (card_num != 0)
    {
        length++;
        card_num = card_num / 10;
    }

    unsigned long prefix = card;
    card = length; // variable "card" is a temporary variable for the lenght

    //While there are more characters than 2 - remove the last digit
    while (length != 2)
    {
        prefix = prefix / 10;
        length--;
    }
    // length is again it original value, geted by the temp. used variable "card"
    length = card;
    bank_cards(prefix, length);
}

// Match the card type
void bank_cards(unsigned long prefix, int length)
{

    if ((length == 13 || length == 16) && (prefix >= 40 && prefix < 50))
    {
        printf("VISA\n");
    }
    else if (length == 16 && (prefix >= 51 && prefix <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if (length == 15 && (prefix == 34 || prefix == 37))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}