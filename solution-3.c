#include "main.h"
/**
 * ptr_print – This prints the value of a pointer variable
 * @types: This List of arguments
 * @buffer: This is a buffer array to handle print
 * @flags:  This calculates active flags
 * @width: This get width
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is a number of characters printed.
 */
int ptr_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_chara = 0, pad = ' ';
	int index = BUFF_SIZE - 2, length = 2, pad_start = 1; /* length=2, for '0x' */
	unsigned long number_addrs;
	char map_to[] = "0123456789abcdef";
	void *adrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (adrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	number_addrs = (unsigned long)adrs;

	while (number_addrs > 0)
	{
		buffer[index--] = map_to[number_addrs % 16];
		number_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_chara = '+', length++;
	else if (flags & F_SPACE)
		extra_chara = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (ptr_write(buffer, index, length,
		width, flags, pad, extra_chara, pad_start));
}
/**
 * print_nothing - printable chars
 * @types: This list of arguments
 * @buffer: This is a buffer array that handles printing
 * @flags:  This calculates the active flags
 * @width: This get width
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is the number of characters printed
 */
int print_nothing(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0, off_s = 0;
	char *string = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		return (write(1, "(null)", 6));

	while (string[a] != '\0')
	{
		if (printable(string[a]))
			buffer[a + off_s] = string[a];
		else
			off_s += append_hexa_code(string[a], buffer, a + off_s);

		a++;
	}

	buffer[a + off_s] = '\0';

	return (write(1, buffer, a + off_s));
}
/**
 * reverse_print – This prints reverse string.
 * @types: This is a List of arguments
 * @buffer: This is a buffer array that handles print
 * @flags:  This calculates the active flags
 * @width: This get width
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is the numbers of characters printed
 */

int reverse_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *string;
	int a, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	string = va_arg(types, char *);

	if (string == NULL)
	{
		UNUSED(precision);

		string = ")Null(";
	}
	for (a = 0; string[a]; a++)
		;

	for (a = a - 1; a >= 0; a--)
	{
		char q = string[a];

		write(1, &q, 1);
		counter++;
	}
	return (counter);
}
/**
 * rot13_print – This Print a string in rot13.
 * @types: This is a list of arguments
 * @buffer: This is a buffer array that handles print
 * @flags:  This is a calculates active flags
 * @width: This is a get width
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is the Numbers of characters printed
 */
int rot13_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char q;
	char *string;
	unsigned int a, b;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	string = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		string = "(AHYY)";
	for (a = 0; string[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == string[a])
			{
				q = out[b];
				write(1, &q, 1);
				counter++;
				break;
			}
		}
		if (!in[b])
		{
			q = string[a];
			write(1, &q, 1);
			counter++;
		}
	}
	return (counter);
}
