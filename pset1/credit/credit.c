// Author: Marko Solajic

#include <cs50.h>
#include <stdio.h>

int get_digit(long number);
void determine_card_type(long number, int sum_final);

int main(void)
{
    int sum_double = 0;
    int sum_single = 0;

    // prompts the user for a number
    long number = get_long("Number: ");

    // calculate the sum via luhn's algorithm
    for (long i = number / 10; i >= 1; i /= 100)
    {
        int digit = get_digit(i) * 2;
        if (digit >= 10)
        {
            digit = (digit / 10) + (digit % 10);
        }
        sum_double += digit;
    }

    for (long i = number; i >= 1; i /= 100)
    {
        int digit = get_digit(i);
        sum_single += digit;
    }
    int sum_final = sum_double + sum_single;

    determine_card_type(number, sum_final);
}

// gets each digit
int get_digit(long number)
{
    int digit = number % 10;
    return digit;
}

// reports the valid card type or if it's invalid
void determine_card_type(long number, int sum_final)
{
    long amex_prefix = 10000000000000;
    long mastercard_prefix = 100000000000000;
    long visa_prefix_13 = 1000000000000;
    long visa_prefix_16 = 1000000000000000;

    if (sum_final % 10 == 0)
    {
        if (number / amex_prefix == 34 || number / amex_prefix == 37)
        {
            printf("AMEX\n");
        }
        else if (number / mastercard_prefix >= 51 && number / mastercard_prefix <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (number / visa_prefix_13 == 4 || number / visa_prefix_16 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
