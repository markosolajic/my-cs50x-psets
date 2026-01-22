// Author: Marko Solajic

#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    int quarters;
    int dimes;
    int nickels;
    int pennies;

    // ask for cents owed
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // calculates cents
    quarters = calculate_quarters(cents);
    cents -= quarters * 25;

    dimes = calculate_dimes(cents);
    cents -= dimes * 10;

    nickels = calculate_nickels(cents);
    cents -= nickels * 5;

    pennies = calculate_pennies(cents);
    cents -= pennies * 1;

    // calculates sum of the coins
    int sum = quarters + dimes + nickels + pennies;
    printf("%i\n", sum);
}

// calculate quarters
int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents -= 25;
    }
    return quarters;
}

// calculate dimes
int calculate_dimes(int cents)
{
    int dimes = 0;
    while (cents >= 10)
    {
        dimes++;
        cents -= 10;
    }
    return dimes;
}

// calculate nickels
int calculate_nickels(int cents)
{
    int nickels = 0;
    while (cents >= 5)
    {
        nickels++;
        cents -= 5;
    }
    return nickels;
}

// calculate pennies
int calculate_pennies(int cents)
{
    int pennies = 0;
    while (cents >= 1)
    {
        pennies++;
        cents -= 1;
    }
    return pennies;
}
