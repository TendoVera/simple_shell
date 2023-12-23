#include "shell.h"
/**
*_strlen - returns length of a string.
*@s: a pointer to an int.
*
*Return: length of string.
*/
int _strlen(char *s)
{
int len = 0;

while (s[len] != '\0')
{
len++;
}
return (len);
}
