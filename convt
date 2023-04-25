#include "main.h"

/**
 * printable - Evaluates if a character is printable or not
 * @c: Char to be evaluated.
 *
 * Return: It will return one if c is printable if not then zero
 */
int printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code 
 * @buffer: This is an array of characters.
 * @a: This is the index that appending will commence.
 * @ascii_code: Code
 * Return: This will always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int a)
{
	char map_to[] = "0123456789ABCDEF";
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[a++] = '\\';
	buffer[a++] = 'x';

	buffer[a++] = map_to[ascii_code / 16];
	buffer[a] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a character is a digit or not
 * @ch: This is the Character to be evaluated
 *
 * Return: It will return 1 if ch is a digit if not then 0
 */
int is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number – It will cast a number to the specific size
 * @number: This is the number to be cast
 * @size: This is the number indicating the type to be casted.
 *
 * Return: This is the cast value of number
 */
long int convert_size_number(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsgnd – This will cast a number to the specific size
 * @number: This is the number to be casted
 * @size: This is the number indicating the type to be casted
 *
 * Return: This is the casted value of number
 */
long int convert_size_unsgnd(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
