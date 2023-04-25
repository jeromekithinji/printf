#include "main.h"
#include <stdarg.h> 
#include <unistd.h> 

/**
 * _printf - produces output according to a format.
 *
 * @format: character string
 * Return: number of characters printed
 */

int _printf(const char *format, ...)
{
	va_list args; 
	int count = 0;
	char *str;
	char c;

	va_start(args, format); 

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case 'c':
				c = va_arg(args, int); 
				write(1, &c, 1);
				count++; 
				break;
			case 's': 
				str = va_arg(args, char *);
				if (!str)
					str = "(null)";
				while (*str)
				{
					write(1, str, 1);
					str++;
					count++;
				}
				break;
			case '%':
				write(1, "%", 1);
				count++;
				break;
			default:
				write(1, "%", 1);
				write(1, &(*format), 1);
				count += 2; 
				break;
			}
		}
		else 
		{
			write(1, &(*format), 1);
			count++;
		}
		format++; 
	}
	va_end(args);

	return (count); 
}
