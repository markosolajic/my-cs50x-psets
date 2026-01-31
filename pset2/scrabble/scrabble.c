// Author: Marko Solajic

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int POINTS[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_score(string player);

int main(void)
{
    string player_1 = get_string("Player 1: ");
    string player_2 = get_string("Player 2: ");

    // calculate the score
    int score_1 = calculate_score(player_1);
    int score_2 = calculate_score(player_2);

    // compare points
    if (score_1 > score_2)
    {
        printf("Player 1 wins!");
    }
    else if (score_1 < score_2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}

int calculate_score(string player)
{
    int score = 0;
    for (int i = 0; i < strlen(player); i++)
    {
        if (isupper(player[i]))
        {
            score += POINTS[player[i] - 'A'];
        }
        else if (islower(player[i]))
        {
            score += POINTS[player[i] - 'a'];
        }
    }
    return score;
}
