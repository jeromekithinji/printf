#include "main.h"

/**
 * size_get - Calculates the size modifier in a string
 *
 * @format: A pointer to a formatted string
 * @a: Pointer of index of last processed character
 *
 * Return: Size modifier
 */

int size_get(const char *format, int *a)
{
	int curr_y = *a + 1;
	int size_modifier = 0;

	if (format[curr_y] == 'l')
		size_modifier = S_LONG;
	else if (format[curr_y] == 'h')
		size_modifier = S_SHORT;

	if (size_modifier == 0)
		*a = curr_y - 1;
	else
		*a = curr_y;

	return (size_modifier);
}
