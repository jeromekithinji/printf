#include "main.h"
/**
 * character_print – This Prints a character now
 * @types: This list of arguments in the function 
 * @buffer: This is a buffer array that handles printing
 * @flags:  This calculates all active flags in the function
 * @width: This is the width definition
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is the number of characters outputted
 */
int character_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (write_character(ch, buffer, flags, width, precision, size));
}
/**
 * str_print – This serves the work of printing a string
 * @types: This is a list of all arguments
 * @buffer: This is a buffer array that handles printing
 * @flags:  This calculates all active flags
 * @width: This is the width.
 * @precision: This is the precision specification
 * @size: This is the size specifier
 * Return: This is the number of characters outputted
 */
int str_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (a = width - len; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - len; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/**
 * percentage_print - 	This prints a % sign
 * @types: This is a list of all arguments
 * @buffer: This is a buffer array that handles printing
 * @flags:  This calculates all active flags
 * @width: This is the width.
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is the number of characters printed
 */
int percentage_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/**
 * integer_print – This prints integers
 * @types: This is a list of all arguments
 * @buffer: This is a buffer array that handles outputting
 * @flags: This calculates all active flags
 * @width: This is the width.
 * @precision: This is the precision specification
 * @size: This is the size specifier
 * Return: This is the number of characters outputted
 */
int integer_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_neg = 0;
	long int b = va_arg(types, long int);
	unsigned long int number;

	b = convert_size_number(b, size);

	if (b == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)b;

	if (b < 0)
	{
		number = (unsigned long int)((-1) * b);
		is_neg = 1;
	}

	while (number > 0)
	{
		buffer[a--] = (number % 10) + '0';
		number /= 10;
	}

	a++;

	return (string_write(is_neg, a, buffer, flags, width, precision, size));
}
/**
 * binary_print – This prints an unsigned number
 * @types: This is a list of all arguments
 * @buffer: This is a buffer array that handles outputting
 * @flags: This calculates all active flags
 * @width: This is the width.
 * @precision: This is a precision specification
 * @size: This is a size specifier
 * Return: This is the number of characters outputted
 */
int binary_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int b, d, c, summ;
	unsigned int a[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	b = va_arg(types, unsigned int);
	d = 2147483648; /* (2 ^ 31) */
	a[0] = b / d;
	for (c = 1; c < 32; c++)
	{
		d /= 2;
		a[c] = (b / d) % 2;
	}
	for (c = 0, summ = 0, counter = 0; c < 32; c++)
	{
		summ += a[c];
		if (summ || c == 31)
		{
			char x = '0' + a[c];

			write(1, &x, 1);
			counter++;
		}
	}
	return (counter);
}
