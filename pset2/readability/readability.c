// Author: Marko Solajic

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_words(string text);
int count_letters(string text);
int count_sentences(string text);

int main(void)
{
    // ask for text
    string text = get_string("Text: ");

    // calculate words, letters, sentences
    float words = count_words(text);
    float letters = count_letters(text);
    float sentences = count_sentences(text);

    // the average number of letters (L) and the sentences (S) per 100 words
    float L = (letters / words) * 100.0;
    float S = (sentences / words) * 100.0;

    // use the Coleman-Liau index
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    // print grade number, and also be careful with 16+ and before grade 1
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words + 1;
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
