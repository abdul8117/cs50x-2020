#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // all coins
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    // user input
    float change;
    do
    {
        change = get_float("Change owed: ");
    } while (change < 0);

    // convert dollars into cents
    change = round(change * 100);

    // loops to determine the number of coins needed
    int coins = 0;

    // no. of quarters
    while (change - quarter >= 0)
    {
        change -= quarter;
        coins++;
    }

    // no. of dimes
    while (change - dime >= 0)
    {
        change -= dime;
        coins++;
    }

    // no. of nickels
    while (change - nickel >= 0)
    {
        change -= nickel;
        coins++;
    }

    // no. of pennies
    while (change - penny >= 0)
    {
        change -= penny;
        coins++;
    }

    printf("%i\n", coins);
}