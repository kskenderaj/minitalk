/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:03:41 by kskender          #+#    #+#             */
/*   Updated: 2025/07/05 15:48:32 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../include/libft/libft.h"
# include "printf/ft_printf.h"
# include <signal.h>
# include <unistd.h>

typedef struct s_server
{
	unsigned char	c;
	int				bit_count;
	pid_t			client_pid;
	char			*buffer;
	size_t			buff_size;
	size_t			buff_capacity;
	unsigned long	msg_size;
}					t_server;

#endif
