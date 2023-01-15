#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) != 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char letter = rotate(plaintext[i], key);
        printf("%c", letter);
    }
    printf("\n");
}

bool only_digits(string s)
{
    int is_digit = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]))
        {
            is_digit++;
        }
    }
    if (is_digit == strlen(s))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
char rotate(char c, int n)
{
    if (isupper(c))
    {
        int foo = c - 65;
        int bar = (foo + n) % 26;
        bar += 65;
        return bar;
    }
    else if (islower(c))
    {
        int foo = c - 97;
        int bar = (foo + n) % 26;
        bar += 97;
        return bar;
    }
    else
    {
        return c;
    }
}

