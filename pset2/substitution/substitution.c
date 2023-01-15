#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char exchange(char a, string b);

int main(int argc, string argv[])
{
    if (argc != 2 || strlen(argv[1]) != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j] || isalpha(argv[1][i]) == 0)
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char letter = exchange(plaintext[i], argv[1]);
        printf("%c", letter);
    }
    printf("\n");
}

char exchange(char a, string b)
{
    if (isupper(a))
    {
        int i = a - 65;
        a = b[i];
        a = toupper(a);
        return a;
    }
    else if (islower(a))
    {
        int i = a - 97;
        a = b[i];
        a = tolower(a);
        return a;
    }
    else
    {
        return a;
    }
}