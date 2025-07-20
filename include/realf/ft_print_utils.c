/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:23:11 by kskender          #+#    #+#             */
/*   Updated: 2025/03/31 17:23:46 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;
	int	written;
	int	totalwritten;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	totalwritten = 0;
	while (str[i])
	{
		written = write(1, &str[i], 1);
		if (written == -1)
			return (-1);
		totalwritten += written;
		i++;
	}
	return (totalwritten);
}

int	ft_putptr(unsigned long ptr)
{
	int		count;
	int		written;
	size_t	temp;

	count = 0;
	temp = (size_t)ptr;
	if (!ptr)
		return (ft_putstr("0x0"));
	written = ft_putstr("0x");
	if (written == -1)
		return (-1);
	count += written;
	written = ft_putnbr_hexptr(temp);
	if (written == -1)
		return (-1);
	count += written;
	return (count);
}
