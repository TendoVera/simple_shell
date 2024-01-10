#include "shell.h"
/**
*_strcmp - returns length of a string.
*@str1: a pointer to an int.
*@str2: string 2
*Return: length of string.
*/
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
	str1++;
	str2++;
	}
	return (*str1 - *str2);
}
