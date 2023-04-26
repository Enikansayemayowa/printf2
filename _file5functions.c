#include "main.h"
/* FUNCTION TO PRINT CHAR */
/**
 * print_char - Prints a characters
 * @types: types a of arguments
 * @buffer: array of buffer
 * @flags:  Calculations of active flags
 * @width: Width
 * @precision: Precision
 * @size: Size specifier
 * Return: int
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char a = va_arg(types, int);

	return (handle_write_char(a, buffer, flags, width, precision, size));
}
/* FUNCTION TO PRINT A STRING */
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array
 * @flags:  Calculation active flags
 * @width: width.
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: int
 */
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, a;
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
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/* FUNCTION PRINT PERCENT SIGN */
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_percent(va_list types, char buffer[],
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
/* FUNCTION TO PRINT AN INT */
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculations active flags
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: int
 */

int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_size_number(m, size);
	if (m == 0)
		buffer[a--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;
	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}
	a++;
	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}
/* PRINT BINARY */
/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculations active flags
 * @width: width.
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: int
 */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int a, m, j, num;
	unsigned int b[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	a = va_arg(types, unsigned int);
	m = 2147483648;
	b[0] = a / m;
	for (j = 1; j < 32; j++)
	{
		m /= 2;
		b[j] = (a / m) % 2;
	}
	for (j = 0, num = 0, count = 0; j < 32; j++)
	{
		num += b[j];
		if (num || j == 31)
		{
			char z = '0' + b[j];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
