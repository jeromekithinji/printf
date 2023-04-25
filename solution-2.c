#include "main.h"
/**
 * print_unsigned - Prints an unsigned number using conversion
 *
 * @types: List of variable arguments passed to the function
 * @buffer: Array of characters that will hold the printed output
 * @flags:  Number of active flags to be used
 * @width: Minimum width of the output
 * @precision: Precision specification
 * @size: Size of the output
 * Return: Number of characters printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int unsigned_num = va_arg(types, unsigned long int);

	unsigned_num = convert_size_unsgnd(unsigned_num, size);

	if (unsigned_num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (unsigned_num > 0)
	{
		buffer[a--] = (unsigned_num % 10) + '0';
		unsigned_num /= 10;
	}

	a++;

	return (unsigned_write(0, a, buffer, flags, width, precision, size));
}
/**
 * octalNot_print - Prints an unsigned number in octal notation
 *
 * @types: List of arguments to be printed
 * @buffer: Buffer array to handle the print operation
 * @flags:  Stores the active flags for the print operation
 * @width: Minimum characters to be printed
 * @precision: Maximum characters to be printed
 * @size: Size of the argument to be printed
 * Return: Number of characters printed
 */
int octalNot_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int value = va_arg(types, unsigned long int);
	unsigned long int original_num = num;

	UNUSED(width);

	value = convert_size_unsgnd(value, size);

	if (value == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (value > 0)
	{
		buffer[a--] = (value % 8) + '0';
		value /= 8;
	}

	if (flags & F_HASH && original_num != 0)
		buffer[a--] = '0';

	i++;

	return (unsigned_write(0, a, buffer, flags, width, precision, size));
}
/**
 * hexdec_print - Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int hexdec_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexadecimal_print(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/**
 * upper_hexa_print - Prints an unsigned number in upper hexadecimal notation
 *
 * @types: List of arguments to be printed
 * @buffer: Character array to store the formatted output
 * @flags:  Active format flags for the output
 * @width: Minimum width
 * @precision: Precision of output
 * @size: Size of the output
 * Return: Number of characters printed
 */
int upper_hexa_print(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexadecimal_print(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/**
 * hexadecimal_print - Convert a unsigned int to hexadecimal number
 *
 * @types: List of arguments
 * @map_to: Character array 
 * @buffer: Character array that stores the hexadecimal number as string
 * @flags:  Formatting flags for the conversion
 * @flag_ch: Format specifier for the conversion
 * @width: Minimum width of the output
 * @precision: Precision specification of the output
 * @size: Size of the input number
 * Return: Number of characters printed
 */
int hexadecimal_print(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int value = va_arg(types, unsigned long int);
	unsigned long int original_num = value;

	UNUSED(width);

	value = convert_size_unsgnd(value, size);

	if (value == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (value > 0)
	{
		buffer[a--] = map_to[value % 16];
		value /= 16;
	}

	if (flags & F_HASH && original_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	i++;

	return (unsigned_write(0, a, buffer, flags, width, precision, size));
}
