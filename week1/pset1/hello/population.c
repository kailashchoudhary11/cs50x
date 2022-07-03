#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    
    int initialpop;
    do
    {
        initialpop = get_int("Enter starting population size of llamas\n");
    }
    while (initialpop < 9);

    // TODO: Prompt for end size
    
    int finalpop;
    do
    {
        finalpop = get_int("Enter ending population size of llamas\n");
    }
    while (finalpop < initialpop);

    // TODO: Calculate number of years until we reach threshold
    
    int years = 0;
    while (initialpop < finalpop)
    {
        initialpop = initialpop + (initialpop / 3) - (initialpop / 4);
        years++;
    }

    // TODO: Print number of years
    
    printf("Years: %i\n", years);
}