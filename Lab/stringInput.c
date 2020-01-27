#include <stdio.h>
#include "string.h"

main()
{
  char ch;
  char text[80];
  char textCopy[80];
  int i;
  i = 0;
  printf("Enter a string: ");
  ch = getchar();
  printf("The string you entered was: \n");
  while (ch != '\n')
    {
      text[i] = ch;
      i++;
      ch = getchar();
    }
  text[i] = '\0';
  strcpy(textCopy, text);

  //printf("\"%s\"\n",text);
  printf("\"%s\"\n",textCopy);

  if (!strcmp(text,textCopy))
    printf("Strings are the same.\n");
  else 
    printf("Strings are not the same.\n");
}