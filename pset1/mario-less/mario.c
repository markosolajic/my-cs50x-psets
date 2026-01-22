// Author: Marko Solajic

#include <cs50.h>
#include <stdio.h>

void print_row(int height, int row);
int main(void)
{
    // asks user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // printing the pyramid
    for (int i = 1; i <= height; i++)
    {

        print_row(height, i);
    }
}

// function for printing one row
void print_row(int height, int i)
{

    for (int j = 0; j < height - i; j++)
    {
        printf(" ");
    }
    for (int j = 0; j < i; j++)
    {
        printf("#");
    }
    printf("\n");
}
