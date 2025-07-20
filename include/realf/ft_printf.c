/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:30:34 by kskender          #+#    #+#             */
/*   Updated: 2025/03/31 17:27:01 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_format(char format, va_list args)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_putnbr_hex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		count += ft_putptr(va_arg(args, unsigned long));
	else if (format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
			count += ft_handle_format(format[++i], args);
		else
			count += ft_putchar(format[i]);
		i++;
		if (count == -1)
			return (-1);
	}
	va_end(args);
	return (count);
}
