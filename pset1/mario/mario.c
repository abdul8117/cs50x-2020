#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // user input with validation
    int height;
    do
    {
        height = get_int("Height:");
    } while (height < 1 || height > 8);

    // the pyramid
    // first loop: each row
    for (int i = 1; i <= height; i++)
    {
        // number of spaces to the left
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }

        // number of # to the left
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }

        // middle spaces
        printf("  ");

        // number of # to the right
        for (int l = i; l > 0; l--)
        {
            printf("#");
        }

        printf("\n");
    }
}