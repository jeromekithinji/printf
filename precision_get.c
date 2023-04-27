#include "main.h"

/**
 * precision_get – This function calculates the precision for printing
 * @format: This is a formatted string to print all the arguments
 * @a: This is a list of all arguments that will be printed.
 * @list_a: list of arguments.
 *
 * Return: The exact precision.
 */
int precision_get(const char *format, int *a, va_list list_a)
{
	int curr_a = *a + 1;
	int prec = -1;

	if (format[curr_a] != '.')
		return (prec);

	prec = 0;

	for (curr_a += 1; format[curr_a] != '\0'; curr_a++)
	{
		if (is_digit(format[curr_a]))
		{
			prec *= 10;
			prec += format[curr_a] - '0';
		}
		else if (format[curr_a] == '*')
		{
			curr_a++;
			prec = va_arg(list_a, int);
			break;
		}
		else
			break;
	}

	*a = curr_a - 1;

	return (prec);
}
