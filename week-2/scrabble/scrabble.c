#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points_conversion(string player, int array[]);

// Array of all the point values ordered alphabetically
int points_values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                       1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    if (points_conversion(player1, points_values) > points_conversion(player2, points_values))
    {
        printf("Player 1 wins!\n");
    }
    else if (points_conversion(player1, points_values) < points_conversion(player2, points_values))
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Calculate the points for a word by making an equivalence of how much points does a letter count
int points_conversion(string player, int point_values[])
{
    // Convert all lowercase chars to uppercase
    for (int i = 0; i < strlen(player); i++)
    {
        if (islower(player[i]))
        {
            player[i] = toupper(player[i]);
        }
    }

    int count = 0;

    for (int i = 0; i < strlen(player); i++)
    {
        // Check if it is an alphabetic character
        if (isalpha(player[i]))
        {
            // Make the equivalence between both arrays thanks to the positions of alphabetic chars
            // in the ASCII values chart
            int points = point_values[player[i] - 65];
            count += points;
        }
    }
    return count;
}
