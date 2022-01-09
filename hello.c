#include <stdio.h>
#include <cs50.h>

int main(void)
{

    string name;
    printf("Hello..?\n");

    // Get person's name
    name = get_string("What was your name?\n-");
    printf("Hello, %s!\n", name);
}