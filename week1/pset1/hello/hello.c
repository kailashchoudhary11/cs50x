#include<cs50.h>
#include<stdio.h>

int main(void)
{
    //Greeting the user!
    string name = get_string("What is your name? ");
    printf("Hello, %s\n", name);
}