// Author: Marko Solajic

#include <cs50.h>
#include <stdio.h>

void print_row(int height, int i);
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        print_row(height, i);
    }
}
// print one row of pyramid
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
    printf("  ");

    for (int j = 0; j < i; j++)
    {
        printf("#");
    }
    printf("\n");
}
