#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    float words = count_words(text);
    int sentences = count_sentences(text);

    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int total = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            total++;
        }
    }
    return total;
}

int count_words(string text)
{
    int total = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            total++;
        }
    }
    return total;
}

int count_sentences(string text)
{
    int total = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) == 0)
        {
            if (text[i] == 46 || text[i] ==  33 || text[i] == 63)
            {
                total++;
            }
        }
    }
    return total;
}