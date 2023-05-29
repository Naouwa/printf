#include "main.h"

void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - prints function
 * @format: format
 * Return: printed characters
 */
int _printf(const char *format, ...)
{
	int a, printed = 0, printed_characters = 0;
	int precision, width, flags, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_ind++] = format[a];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[a], 1);*/
			printed_characters++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			precision = get_precision(format, &a, list);
			width = get_width(format, &a, list);
			flags = get_flags(format, &a);
			size = get_size(format, &a);
			a++;
			printed = handle_print(format, &a, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_characters);
}
/**
 * print_buffer - prints the contents of buffer
 * @buffer: array of characters
 * @buff_ind: the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
