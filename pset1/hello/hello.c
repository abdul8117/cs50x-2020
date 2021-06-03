#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Name:\n");
    printf("Hello, %s\n", name);
}