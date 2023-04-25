#include "main.h"
/**
 * print_handle - Prints an argument based on formatted string type.
 *
 * @fmt: Pointer to a formatted string.
 * @list: List of arguments.
 * @ind: Pointer to int to keep track of index in fmt.
 * @buffer: Array used to store characters needed to be printed.
 * @flags: Active flags in format string.
 * @width: Minimum characters to be printed.
 * @precision: Number of digits to be printed after decimal point.
 * @size: Size specifier of the format string
 * Return: A number
 */

int print_handle(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int a, unknown_length = 0, chars_printed = -1;
	fmt_t format_types[] = {
		{'c', character_print}, {'s', str_print}, {'%', percentage_print},
		{'i', integer_print}, {'d', integer_print}, {'b', binary_print},
		{'u', print_unsigned}, {'o', octalNot_print}, {'x', hexdec_print},
		{'X', upper_hexa_print}, {'p', ptr_print}, {'S', print_nothing},
		{'r', reverse_print}, {'R', rot13_print}, {'\0', NULL}
	};
	for (a = 0; format_types[a].fmt != '\0'; a++)
		if (fmt[*ind] == format_types[a].fmt)
			return (format_types [a].fn(list, buffer, flags, width, precision, size));

	if (format_types [a].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_length += write(1, &fmt[*ind], 1);
		return (unknown_length);
	}
	return (chars_printed);
}
