#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main()
{
    float letters, words, sentences;
    float index;
    string text = get_string("Insert text:\n");

    words = count_words(text);
    letters = count_letters(text);
    sentences = count_sentences(text);


    letters = letters / words;
    letters = letters * 100;
    sentences = sentences / words;
    sentences = sentences * 100;
    index = (0.0588 * letters - 0.296 * sentences) - 15.8;


    //Print out the grade
    if (index < 1)
    {
        printf("\nBefore Grade 1\n");
    }
    else if (index > 16)
    {
        printf("\nGrade 16+\n");
    }
    else
    {
        printf("\nGrade %.0f\n", index);
    }
}



// Count letters, upper of lower case, excluding other characters
int count_letters(string text)
{
    int letters = 0, i;
    char c;
    for (i = 0; text[i] != '\0'; i++)
    {
        c = tolower(text[i]);
        if (c >= 'a' && c <= 'z')
        {
            letters++;
        }
    }
    return letters;
}


// Count words by the commas and/or spaces better them
int count_words(string text)
{
    int words = 0, i;

    for (i = 0; text[i] != '\0'; i++)
    {

        if (text[i] == ' ')
        {

            //Counts only the last dot of "..."
            if (text[i + 1] == ' ')
            {
                continue;
            }

            words++;
            continue;
        }

        /*If there is not space after a comma,
        we treat this as a start of a new word*/
        if (text[i] == ',' && text[i + 1] != ' ')
        {
            words++;
            continue;
        }
    }
    words++; /* Every space correspond to one word. With experiment
    with random text I discoverd that the first sentence have one " "(space)
    less than any other sentence. */
    return words;
}


// Count sentences by the ending symbol of the sentence
int count_sentences(string text)
{

    int sentences = 0, i;

    for (i = 0; (text[i] != '\0'); i++)
    {
        //Handles exclamation pint and question mark
        if (text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }

        //Handles point and ellipsis(sequence of dots)
        if (text[i] == '.')
        {
            if (text[i + 1] != '.')
            {
                sentences++;
            }
        }
    }

    return sentences;
}



