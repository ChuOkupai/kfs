/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:21:25 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/20 20:39:36 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include "string.h"
#include <stdio.h>
#include "stdio.h"

static bool	print(const char *data, size_t length)
{
	const unsigned char	*bytes = (const unsigned char *) data;

	for (size_t i = 0; i < length; i++)
	{
		if (putchar(bytes[i]) == EOF)
			return (false);
	}
	return (true);
}

static int	print_char(char c)
{
	if (!print(&c, sizeof(c)))
		return (-1);
	return (sizeof(c));
}

static int	print_string(const char *str)
{
	size_t	len;

	len = strlen(str);
	if (!print(str, len))
		return (-1);
	return (len);
}

int	printf_putchar(const char **format, int *written)
{
	int	amount;

	if ((*format)[0] == '%')
		(*format)++;
	amount = 1;
	while ((*format)[amount] && (*format)[amount] != '%')
		amount++;
	if ((INT_MAX - *written) < amount || !print(*format, amount))
		return (-1);
	(*format) += amount;
	(*written) += amount;
	return (0);
}

int	printf_putstr(const char **format, int *written)
{
	int	amount;

	amount = 1;
	while ((*format)[amount] && (*format)[amount] != '%')
		amount++;
	if ((INT_MAX - *written) < amount || !print((*format), amount))
		return (-1);
	(*format) += amount;
	*written += amount;
	return (0);
}

int	printf(const char *format, ...)
{
	va_list	parameters;
	int		written;

	written = 0;
	va_start(parameters, format);
	while (*format != '\0')
	{
		if (format[0] != '%' || format[1] == '%')
		{
			if ((-1) == printf_putchar(&format, &written))
				return (-1);
			continue ;
		}
		format++;
		if (*format != 'c' && *format != 's')
		{
			if ((-1) == printf_putstr(&format, &written))
				return (-1);
			continue ;
		}
		if (*format == 'c')
			written += print_char((char) va_arg(parameters, int));
		else
			written += print_string(va_arg(parameters, const char *));
		format++;
	}
	va_end(parameters);
	return (written);
}
