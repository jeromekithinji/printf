#include <stddef.h>
#include <stdarg.h>
#include "main.h"
void print_buffer(char buffer[], int *buff_index);

/**  * _printf - Prints formatted output.  * @format: Pointer to a str that contains a format str.  *  * Return: Number of characters printed  */
int _printf(const char *format, ...)
{
	int a, output = 0, print_character  = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list arg_list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);
	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_index++] = format[a];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
			prints_char++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &a);
			width = get_width(format, &a, arg_list);
			precision = get_precision(format, &a, arg_list);
			size = get_size(format, &a);
			++a;
			output = handle_print
				(format, &a, arg_list, buffer, flags, width, precision, size);
			if (output == -1)
				return (-1);
			print_character += output;
		}
	}

	print_buffer(buffer, &buff_index);

	va_end(arg_list);

	return (prints_char);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists.
 * @buffer: This is an array of characters.
 * @buff_index: The length is indicated by the index at which the next character should be added.
 */
void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index= 0;
}
