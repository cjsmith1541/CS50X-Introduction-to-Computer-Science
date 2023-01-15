#include <stdio.h>
#include <cs50.h>

int main(void)
// get the persons card number
{
    long counter = 0;
    long total = 0;
    long pre = 0;
    long after = 0;
    long final = 0;
    long firstdiget = 0;
    long visadiget = 0;
    long cardnumber = get_long("Number: ");
    // get last diget then remove it to do the same on next one
    while (cardnumber > 0)
    {
        long diget = (cardnumber % 10);
        cardnumber = (cardnumber / 10);
        counter++;
        if (counter % 2 == 0)
        {
            pre = (diget * 2);
            if (pre > 9)
            {
                after = (pre % 10);
                pre = (pre / 10);
                final = (pre + after);
                total = (total + final);
            }
            else
            {
                total = (total + pre);
            }
        }
        if (cardnumber > 10 && cardnumber < 100)
        {
            firstdiget = (cardnumber);
            visadiget = (cardnumber / 10);
        }
        if (counter % 2 == 1)
        {
            total = (total + diget);
        }
    }
    if (counter == 16 && (firstdiget == 51 || firstdiget == 52 || firstdiget == 53 || firstdiget == 54 || firstdiget == 55)
        && total % 10 == 0)
    {
        printf("MASTERCARD\n");
    }
    else if ((counter == 13 || counter == 16) && visadiget == 4 && total % 10 == 0)
    {
        printf("VISA\n");
    }
    else if (counter == 15 && (firstdiget == 34 || firstdiget == 37) && total % 10 == 0)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}