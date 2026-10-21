#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Choose the height between 1 and 8: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {

        // first spaces
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");
        }

        // First triangle
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Fixed spaces of the middle
        printf("  ");

        // second triangle
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
