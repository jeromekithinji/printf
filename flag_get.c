#include "main.h"

/**
 * flag_get – Gets number of active flags
 *
 * @format: the formatted string
 * @a: pointer to an integer
 * Return: number of active flags
 */

int flag_get(const char *format, int *a)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int x, curr_y;
	int flags = 0;
	const char ch_flags[] = {'-', '+', '0', '#', ' ', '\0'};
	const int arr_flags[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_y = *i + 1; format[curr_y] != '\0'; curr_y++)
	{
		for (x = 0; ch_flags [x] != '\0'; x++)
			if (format[curr_y] == ch_flags [x])
			{
				flags |= arr_flags [x];
				break;
			}

		if (ch_flags [x] == 0)
			break;
	}

	*a = curr_y - 1;

	return (flags);
}
