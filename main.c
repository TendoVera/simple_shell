#include "shell.h"
/**
* main - Entry point for shell.
* Return: (Success) 0.
*/
int main(void)
{
prompt_line();
return (0);
}
/**
* _strcmp - compares two strings
* @str1: First string.
* @str2: Second string.
*
* Return: True if equal.
*/
int _strcmp(const char *str1, const char *str2)
{

	while (*str1 != '\0' && *str2 != '\0')
{

	if (*str1 != *str2)
{
return (0);
}
str1++;
str2++;
}
return (*str1 == *str2);
}
