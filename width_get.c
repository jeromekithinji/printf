#include "main.h"

/**
 * width_get - Calculates the width of the printed output
 *
 * @format: Pointer to a formatted string
 * @a: Pointer to an integer showing current position on format string
 * @list: Argument list
 *
 * Return: Width of output
 */

int width_get(const char *format, int *a, va_list list)
{
	int curr_y;
	int printWidth = 0;

	for (curr_y = *a + 1; format[curr_y] != '\0'; curr_y++)
	{
		if (is_digit(format[curr_y]))
		{
			printWidth *= 10;
			printWidth += format[curr_y] - '0';
		}
		else if (format[curr_y] == '*')
		{
			curr_y++;
			printWidth = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*a = curr_y - 1;

	return (printWidth);
}
