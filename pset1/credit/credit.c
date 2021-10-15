#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int luhn_check(long input);

int main(void)
{
    // VARIABLE DEFINITIONS
    long            input;
    unsigned int    digit_length;
    unsigned int    first2no;
    unsigned int    firstno;
    // USER INPUT PROMPT
    input = get_long("Number: ");

    // CREATE LOGIC
    digit_length = (unsigned int) log10(input) + 1;
    first2no = input / pow(10, digit_length - 2);
    firstno = input / pow(10, digit_length - 1);
    
    // CHECK IF VALID AMEX
    if (digit_length == 15 && (first2no == 34 || first2no == 37) && luhn_check(input))
    {
        printf("AMEX\n");
    }
    // CHECK IF VALID MASTERCARD    
    else if (digit_length == 16 && (first2no == 51 || first2no == 52 || first2no == 53 || first2no == 54 || first2no == 55)
             && luhn_check(input))
    {
        printf("MASTERCARD\n");
    }
    // CHECK IF VALID VISA
    else if ((digit_length == 13 || digit_length == 16) && firstno == 4 && luhn_check(input))
    {
        printf("VISA\n");
    }
    // ELSE INVALID
    else
    {
        printf("INVALID\n");
    }
}

int luhn_check(long input)
{
    // VARIABLE DEFINITIONS
    unsigned int    current;
    unsigned int    checksum1;
    unsigned int    checksum2;
    unsigned int    other;
    unsigned int    result;    

    // STEP 1 OF ALGORITHM: every other number starting from the 2nd to last
    checksum1 = 0;
    checksum2 = 0;
    other = 0;
    while (input > 0)
    {
        current = input % 10; // multiply by 2
        // REDUCE CURRENT INTO THE SUM OF ITS DIGITS (can be max 18)
        if (other % 2 == 0)
        {
            checksum1 += current; // add current to checksum
        }
        else if (other % 2 == 1)
        {
            current *= 2;
            current = current % 10 + current / 10; // should always be valid 
            checksum2 += current;
        }
        other++;
        input /= 10;
    }
    result = checksum1 + checksum2;
    if (result % 10 == 0)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}
