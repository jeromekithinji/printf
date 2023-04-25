#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Prints formatted output.
 * @format - Pointer to a str that contains a format str.
 *
 * Return - Number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list argument;
    int print_ch = 0;

    va_start(argument , format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;

            switch (*format)
            {
                case 'c':
                    print_ch += write(1, (char) va_arg(argument , int), 1);
                    break;

                case 's':
                    print_ch += write(1, va_arg(argument , char *), 1);
                    break;

                case '%':
                    print_ch += write(1, "%", 1);
                    break;

                default:
                    print_ch += write(1, "%", 1);
                    print_ch += write(1, format, 1);
                    break;
            }
        }
        else
        {
            print_ch += write(1, format, 1);
        }

        format++;
    }

    va_end(argument );

    return (printed_chars);
}

