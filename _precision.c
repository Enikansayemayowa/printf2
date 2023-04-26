#include "main.h"
/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string
 * @j: List of arguments
 * @list: list of arguments.
 * Return: int
 */
int get_precision(const char *format, int *j, va_list list)
{
	int curr_i = *j + 1;
	int prec = -1;

	if (format[curr_i] != '.')
		return (prec);
	prec = 0;
	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			prec *= 10;
			prec += format[curr_i] - '0';
		}
		else
			if (format[curr_i] == '*')
			{
				curr_i++;
				prec = va_arg(list, int);
				break;
			}
			else
				break;
	}
	*j = curr_i - 1;
	return (prec);
}
