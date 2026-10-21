#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int number_letters(string text);
int number_words(string text);
int number_sentences(string text);

int main(void)
{
    string text = get_string("Text: \n");
    // Coleman-Liau index calculation
    float L = ((float) number_letters(text) / number_words(text)) * 100;
    float S = ((float) number_sentences(text) / number_words(text)) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// We count a letter if a character is alphabetic
int number_letters(string text)
{
    int letter_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter_count += 1;
        }
    }
    return letter_count;
}

// The separation between two words is the space, used as distinction for counting words
int number_words(string text)
{
    int word_count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            word_count++;
        }
    }
    return word_count;
}

// A sentence finishes if '.', '?' or '!' appears
int number_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}
