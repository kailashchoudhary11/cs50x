#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include<math.h>
#include<stdlib.h>

int main(int argc, string argv[])
{



  char str[20];
  char *ptr[20];
  for (int i=0;i<20;i++)
  {
      ptr[i]=&str[i];
  }
  for(int i=0; i<5; i++){
  printf("Enter char\n");
  scanf("%c", &str[i]);
  }
  printf("%s\n", str);

}