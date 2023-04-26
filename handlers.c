#include "main.h"

/**
 * write_character – Writes a character to the output 
 *
 * @c: Character to be printed
 * @buffer: Buffer array used to handle the print
 * @flags:  Stores the active formatting flags
 * @width: Minimum width of the printed string
 * @precision: Integer specifying the precision of the printed string
 * @size: Size specifier for the printed string
 *
 * Return: Number of characters printed
 */
int write_character(char c, char buffer[],
	int flags, int width, int precision, int size)
{	
	int a = 0;
	char padding_char = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding_char = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = padding_char;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * string_write - Prints a string
 *
 * @is_negative: int indicating if the input string is negative
 * @ind: The index where the string starts in the buffer
 * @buffer: Buffer array that holds the string to be printed
 * @flags: Active flags for the string
 * @width: Minimum width of the printed string
 * @precision: Number of digits to be printed after the decimal point
 * @size: The size for the specifier for the string
 *
 * Return: Number of chars printed.
 */
int string_write(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int bufferLength = BUFF_SIZE - ind - 1;
	char padding_char = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding_char = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (number_write(ind, buffer, flags, width, precision,
		bufferLength, padding_char, extra_ch));
}

/**
 * number_write - Write a number to the buffer
 *
 * @ind: Index where the number starts on the buffer
 * @buffer: Buffer to write the number to
 * @flags: Flags to decide to print number as a signed or unsigned integer
 * @width: Minimum width of the field
 * @prec: The Precision specifier
 * @length: Length of the number to be printed
 * @padd: Padding character to use if the width of the field is greater
 * than the length of the number
 * @extra_c: Extra character to print before the number
 *
 * Return: Number of characters printed
 */

int number_write(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int a, padding_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padding_start] = extra_c;
			return (write(1, &buffer[padding_start], a - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * unsigned_write - Writes an unsigned number to the buffer
 *
 * @is_negative: Shows if the number is negative
 * @ind: Index where the number starts in the buffer
 * @buffer: Array of characters representing the buffer
 * @flags: Flags for the format specifiers
 * @width: The width specifier
 * @precision: The precision specifier
 * @size: The size specifier
 *
 * Return: Number of written characters written to the output stream
 */

int unsigned_write(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int num_chars = BUFF_SIZE - ind - 1, a = 0;
	char padding_char = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); 
	if (precision > 0 && precision < num_chars)
		padding_char = ' ';

	while (precision > num_chars)
	{
		buffer[--ind] = '0';
		num_chars++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding_char = '0';

	if (width > num_chars)
	{
		for (a = 0; a < width - num_chars; a++)
			buffer[a] = padding_char;

		buffer[a] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], num_chars) + write(1, &buffer[0], a));
		}
		else
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], num_chars));
		}
	}

	return (write(1, &buffer[ind], num_chars));
}

/**
 * ptr_write - Write a memory address to the output
 *
 * @buffer: Arrays of characters to store the memory address
 * @ind: Index at which the memory address starts in the buffer
 * @length: Length of the memory address
 * @width: The width specifier
 * @flags: The flags specifier
 * @padd: The padding charater
 * @extra_c: Extra character that may be needed to be written
 * @padd_start: The index at which padding should start
 *
 * Return: Number of written characters
 */
int ptr_write(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
