/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:14:51 by kskender          #+#    #+#             */
/*   Updated: 2025/07/14 11:31:13 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#define MAX_MSG_SIZE 1000000

static void	init_server(t_server *s, pid_t new_pid)
{
	s->c = 0;
	s->bit_count = 0;
	s->client_pid = new_pid;
	if (s->buffer)
	{
		free(s->buffer);
		s->buffer = NULL;
	}
	s->buff_size = 0;
	s->buff_capacity = 0;
	s->msg_size = 0;
}

static void	handle_char(t_server *s)
{
	ft_printf("are we in handle_char?\n");
	if (!s->buffer || s->buff_size >= s->buff_capacity)
	{
		ft_putstr_fd("Error: Buffer overflow\n", 2);
		free(s->buffer);
		exit(EXIT_FAILURE);
	}
	if (s->c == '\0')
	{
		s->buffer[s->buff_size] = '\0';
		write(1, "Received: ", 10);
		write(1, s->buffer, s->buff_size);
		write(1, "\n", 1);
		free(s->buffer);
		s->buffer = NULL;
		s->buff_size = 0;
		s->buff_capacity = 0;
	}
	else
	{
		s->buffer[s->buff_size++] = s->c;
	}
	s->c = 0;
	s->bit_count = 0;
}

static void	handle_size(t_server *s)
{
	ft_printf("Are we in handle_size?\n");
	s->msg_size = (s->msg_size << 1) | (s->c & 1);
	s->bit_count++;
	if (s->bit_count == 64)
	{
		if (s->msg_size > MAX_MSG_SIZE)
		{
			ft_putstr_fd("Error: Message too large\n", 2);
			free(s->buffer);
			exit(EXIT_FAILURE);
		}
		s->buffer = malloc(s->msg_size + 1);
		if (!s->buffer)
			exit(EXIT_FAILURE);
		s->buff_capacity = s->msg_size + 1;
		s->bit_count = 0;
	}
	s->c = 0;
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static t_server	s;

	(void)context;
	if (s.client_pid == 0 || s.client_pid != info->si_pid)
	{
		init_server(&s, info->si_pid);
		ft_printf("Hey we init the server\n");
	}
	s.c = (s.c << 1) | (sig == SIGUSR2);
	// handle_size(&s);
	s.bit_count++;
	if (s.bit_count == 8)
	{
		// ft_printf("Are we ever here\n");
		if (s.buff_capacity == 0)
			handle_size(&s);
		else
			handle_char(&s);
		s.c = 0;
		s.bit_count = 0;
	}
	kill(s.client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("SERVER PID: %d\n", getpid());
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("ERROR: SIGUSR1 setup failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("ERROR: SIGUSR2 setup failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
