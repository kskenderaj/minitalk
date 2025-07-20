/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:22:56 by kskender          #+#    #+#             */
/*   Updated: 2025/04/07 15:58:11 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putnbr_hex(unsigned int n, char format);
int	ft_putnbr_hexptr(size_t n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putnbr(int n);
int	ft_putstr(char *str);
int	ft_putchar(char c);
int	ft_putptr(unsigned long ptr);

#endif