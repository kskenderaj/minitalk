/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:03:41 by kskender          #+#    #+#             */
/*   Updated: 2025/07/14 12:49:11 by kskender         ###   ########.fr       */
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
	char	current_char;
	int		bit_count;
	pid_t	client_pid;
	char	*message;
	size_t	msg_len;
	size_t	msg_capacity;
}			t_server;

#endif
