#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void crypt(string key, string text);
bool validating_key_input(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    string text, key = argv[1];


    bool key_status = validating_key_input(key);

    if (!(key_status))
    {
        return 1;
    }



    if (key_status)
    {
        text = get_string("plaintext: ");
        crypt(key, text);
    }

    return 0;
}

bool validating_key_input(string key)
{
    int i, k;
    char c;
    // Check is the key 25 characters long
    if (strlen(key) != 26)
    {
        printf("Your key must contain 26 characters.\n");
        return false;
    }

    // Checks are there non-letters
    for (i = 0; key[i] != '\0'; i++)
    {
        c = tolower(key[i]);
        if (c < 'a' || c > 'z')
        {
            return false;
        }
    }

    // Check are there repeating characters in the key
    for (i = 0; key[i] != '\0'; i++)
    {
        for (k = 0; key[k] != '\0'; k++)
        {
            if ((toupper(key[i]) == toupper(key[k])) && (i != k))
            {
                return false;
            }
        }
    }

    return true;

}



// Functuon thats crypt the ciphertext
void crypt(string key, string text)
{
    printf("ciphertext: ");
    for (int i = 0; text[i] != '\0'; i++)
    {
        // If the letter is uppercase, use key and print it as uppercase
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            for (int k = 0; key[k] != '\0'; k++)
            {
                // Find the corresponding index in the key
                if (((int)text[i] - 65) == k)
                {
                    printf("%c", toupper(key[k]));
                    break;
                }
            }
            continue;
        }

        // If the letter is lowercase, use key and print it as lowercase
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            for (int k = 0; key[k] != '\0'; k++)
            {
                // Find the corresponding index in the key
                if (((int)text[i] - 97) == k)
                {
                    printf("%c", tolower(key[k]));
                    break;
                }
            }
            continue;
        }
        printf("%c", text[i]);
    }
    printf("\n");
}