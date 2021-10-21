#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// CS50 PSET2: SUBSTITUTION
// AUTHOR: HENDRIK JACQUES VAN HOVE

int check_invalid_key(char *input)
{
    // INVALID LENGTH
    if (strlen(input) != 26)
    {
        printf("Key must contain 26 characters.");
        return (1);
    }

    // DUPLICATE ENTRY
    int i = 0;
    int j;
    while (input[i] != '\0')
    {
        j = i + 1;
        while (input[j] != '\0')
        {
            if (input[i] == input[j])
            {
                printf("Duplicate entry in the key.");
                return (1);
            }
            j++;
        }
        i++;
    }

    // NON-ALPHABETIC ENTRY
    i = 0;
    while (input[i] != '\0')
    {
        if (!isalpha(input[i]))
        {
            printf("Non-alphabetic entry in the key");
            return (1);
        }
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    // User doesn't cooperate
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return (1);
    }
    
    // Invalid key
    else if (check_invalid_key(argv[1]))
    {
        {
            return (1);
        }
    }
    
    // Normal usage
    else
    {
        string input = get_string("plaintext: "); // hello there
        char output[strlen(input)]; // empty array with same space
        int i = 0;
        
        while (i < strlen(input)) // iterate over input
        {
            if (islower(input[i])) // 
            {
                output[i] = tolower(argv[1][input[i] - 97]);
            }
            else if (isupper(input[i]))
            {
                output[i] = toupper(argv[1][input[i] - 65]);
            }
            else 
            {
                output[i] = input[i];
            }
            i++;
        }
        output[i] = '\0'; // ending the output
        printf("ciphertext: %s\n", output);
    }
    return (0);
}
