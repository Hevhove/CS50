#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    int input;

    // Prompt user for input
    do
    {
        input = get_int("Height: ");
    }
    while (input < 1 || input > 8);

    // Outer loop
    for (int i = 0; i < input; i++) // input = 8, i = 0
    {
        // Left whitespace
        for (int j = input - i - 1 ; j > 0; j--)
        {
            printf(" ");
        }

        // Left hashtags
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        // Middle whitespace
        printf("  ");

        // Right hashtags
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }

        // Right spaces
        //for (int m = input - i - 1; m > 0; m--)
        //{
        //    printf(" ");
        //} 
        // Print a new line
        printf("\n");
    }
}
