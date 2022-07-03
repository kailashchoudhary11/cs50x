#include<cs50.h>
#include<stdio.h>

void print_spaces(int);
void print_hashes(int);
void print_pyramid(int);

int main(void)
{
    // Taking Height from User
    
    int height;
    do
    {
        height = get_int("Enter height\n");
    }
    while (height < 1 || height > 8);
    
    // Printing the pyramid
    
    print_pyramid(height);
}


void print_spaces(int n)
{
    //printing spaces
    
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
    
}

void print_hashes(int n)
{
    // printing blocks
    
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

void print_pyramid(int height)
{
    int k = height - 1;
    
    for (int i = 0; i < height; i++)
    {
        print_spaces(k);
        print_hashes(i + 1);
        print_spaces(2);
        print_hashes(i + 1);
        printf("\n");
        k--;
    }
}