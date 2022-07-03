#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float dollars;
    
    // inputs change owed from user
    do
    {
        dollars = get_float("Enter change owed\n");
    }
    while (dollars < 0);
    
    int cents = round(dollars * 100);
    int coins = 0;
    
    // counts minimum coins required
    
    while (cents != 0)
    {
        
        if (cents >= 25)
        {
            cents = cents - 25;
            coins++;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
            coins++;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
            coins++;
        }
        else
        {
            cents = cents - 1;
            coins++;
        }
    }
    printf("Total coins to be given: %i\n", coins);
}