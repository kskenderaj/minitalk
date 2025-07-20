/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:24:32 by kskender          #+#    #+#             */
/*   Updated: 2025/03/31 18:59:39 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	count;
	int	temp;

	count = 0;
	temp = 0;
	if (n == -2147483648)
	{
		if ((write(1, "-2147483648", 11) == -1))
			return (-1);
		return (11);
	}
	if (n < 0 && count++ == 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		n = -n;
	}
	if (n > 9)
		temp = ft_putnbr(n / 10);
	if (temp == -1)
		return (-1);
	count += temp;
	if (write(1, &(char){n % 10 + '0'}, 1) == -1)
		return (-1);
	return (count + 1);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int		count;
	char	c;
	int		temp;

	count = 0;
	if (n >= 10)
	{
		temp = ft_putnbr_unsigned(n / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	c = (n % 10) + '0';
	temp = write(1, &c, 1);
	if (temp == -1)
		return (-1);
	count += temp;
	return (count);
}

int	ft_putnbr_hex(unsigned int n, char format)
{
	int		count;
	char	*base;

	count = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		count += ft_putnbr_hex(n / 16, format);
		if (count == -1)
			return (-1);
	}
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_putnbr_hexptr(size_t n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
	{
		count += ft_putnbr_hexptr(n / 16);
		if (count == -1)
			return (-1);
	}
	count += ft_putchar(base[n % 16]);
	return (count);
}
