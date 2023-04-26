#include "main.h"
/* PRINT POINTER */
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char c = 0, pointer = ' ';
	int ind = BUFF_SIZE - 2, _length = 2, pointer_start = 1;
	unsigned long number_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);
	if (address == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	number_address = (unsigned long)address;
	while (number_address > 0)
	{
		buffer[ind--] = map_to[number_address % 16];
		number_address /= 16;
		_length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pointer = '0';
	if (flags & F_PLUS)
		c = '+', _length++;
	else if (flags & F_SPACE)
		c = ' ', _length++;
	ind++;
	return (write_pointer(buffer, ind, _length,
				width, flags, pointer, c, pointer_start));
}
/* FUNCTION TO PRINT NON PRINTABLE */
/**
 * print_non_printable - Prints ascii codes in hexa
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculation of  active flags
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: int
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int j = 0, offset = 0;
	char *ptr = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (ptr == NULL)
		return (write(1, "(null)", 6));
	while (ptr[j] != '\0')
	{
		if (is_printable(ptr[j]))
			buffer[j + offset] = ptr[j];
		else
			offset += append_hexa_code(ptr[j], buffer, j + offset);
		j++;
	}
	buffer[j + offset] = '\0';
	return (write(1, buffer, j + offset));
}
/* FUNCTION TO PRINT REVERSE */
/**
 * print_reverse - Prints reverse string.
 * @types: Lists of arguments
 * @buffer: Buffer array
 * @flags: Calculations active flags
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: int
 */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *ptr;
	int j, cnt = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	ptr = va_arg(types, char *);
	if (ptr == NULL)
	{
		UNUSED(precision);
		ptr = ")Null(";
	}
	for (j = 0; ptr[j]; j++)
		;
	for (j = j - 1; j >= 0; j--)
	{
		char y = ptr[j];

		write(1, &y, 1);
		cnt++;
	}
	return (cnt);
}
/* FUNCTION TO PRINT A STRING IN ROT13 */
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lists of arguments
 * @buffer: Buffer array
 * @flags:  Calculation active flags
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: int
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char y;
	char *ptr;
	unsigned int j, k;
	int cnt = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	ptr = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (ptr == NULL)
		ptr = "(AHYY)";
	for (j = 0; ptr[j]; j++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == ptr[j])
			{
				y = out[k];
				write(1, &y, 1);
				cnt++;
				break;
			}
		}
		if (!in[k])
		{
			y = ptr[j];
			write(1, &y, 1);
			cnt++;
		}
	}
	return (cnt);
}

