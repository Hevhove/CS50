#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// CS50: PROBLEM SET 2
// IMPLEMENTATION OF THE COLEMAN-LIAU INDEX
// AUTHOR: HENDRIK JACQUES VAN HOVE

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);

int main(void)
{
    // USER INPUT
    string input = get_string("Text: ");  
    
    int letters = count_letters(input);
    int words = count_words(input);
    int sentences = count_sentences(input);

    // CALCULATE L AND S
    float L = letters * (100 / (float) words);
    float S = sentences * (100 / (float) words);
    int result = round(0.0588 * L - 0.296 * S - 15.8);
    
    // printf("%d letter(s)\n", letters);
    // printf("%d word(s)\n", words);
    // printf("%d sentence(s)\n", sentences);
    // printf("L, S are: %f, %f\n", L, S);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", result);
    }

    return (0);
}

int count_letters(string input)
{
    int i = 0;
    int count = 0;

    while (input[i] != '\0')
    {
        if (isalpha(input[i]))
        {
            count++;
        }
        i++;
    }
    return (count);
}

int count_words(string input)
{
    int i = 0;
    int count = 0;
    
    while (input[i] != '\0')
    {
        if (input[i] == ' ' && i != 0)
        {
            count++;
        }
        i++;
    }
    count++;
    return (count);
}

int count_sentences(string input)
{
    int i = 1;
    int count = 0;
    
    while (input[i] != '\0')
    {
        if ((input[i] == '.' || input[i] == '!' || input [i] == '?') && (isalpha(input[i - 1])))
        {
            count++;
        }
        i++;
    } 
    return (count);
}
