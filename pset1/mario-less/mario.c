#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //row
    for (int i = 0; i < height; i++)
    {
        //collum
        for (int j = 0; j < height; j++)
        {
            if (j < height - (i + 1))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }


}