#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ciphertext(string plaintext, int key);

int main(int argc, string argv[])
{
    // checking command line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    if (key <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Taking input from user
    string plaintext = get_string("plaintext: ");
    // printing ciphertext
    ciphertext(plaintext, key);

    return 0;
}

void ciphertext(string plaintext, int key)
{
    char lowercase[26];
    char uppercase[26];
    lowercase[0] = 'a';
    uppercase[0] = 'A';
    int n = strlen(plaintext);
    int p[n];


    // finding P(i)
    for (int j = 1; j < 26; j++)
    {
        lowercase[j] = lowercase[j - 1] + 1;
        uppercase[j] = uppercase[j - 1] + 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (islower(plaintext[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == lowercase[j])
                {
                    p[i] = j;
                }
            }
        }
        else if (isupper(plaintext[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == uppercase[j])
                {
                    p[i] = j;
                }
            }
        }
    }
    // Finding C(i)
    int c[n];
    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                c[i] = (p[i] + key) % 26;
                plaintext[i] = lowercase[c[i]];
            }
            else if (isupper(plaintext[i]))
            {
                c[i] = (p[i] + key) % 26;
                plaintext[i] = uppercase[c[i]];
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
}
