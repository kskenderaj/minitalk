/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:47:40 by kskender          #+#    #+#             */
/*   Updated: 2025/07/14 20:48:33 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	init_server(t_server *s, pid_t new_pid)
{
	s->current_char = 0;
	s->bit_count = 0;
	s->client_pid = new_pid;
	if (s->message)
		free(s->message);
	s->message = NULL;
	s->msg_len = 0;
	s->msg_capacity = 0;
}

static void	handle_char(t_server *s)
{
	char	*new_msg;

	if (s->msg_len >= s->msg_capacity)
	{
		s->msg_capacity += 1024;
		new_msg = realloc(s->message, s->msg_capacity);
		if (!new_msg)
		{
			free(s->message);
			exit(EXIT_FAILURE);
		}
		s->message = new_msg;
	}
	s->message[s->msg_len++] = s->current_char;
	if (s->current_char == '\0')
	{
		write(STDOUT_FILENO, s->message, s->msg_len);
		write(STDOUT_FILENO, "\n", 1);
		free(s->message);
		s->message = NULL;
		s->msg_len = 0;
		s->msg_capacity = 0;
		if (kill(s->client_pid, SIGUSR2) == -1)
			ft_putstr_fd("Warning: Failed to send message ACK\n",
							STDERR_FILENO);
	}
	s->current_char = 0;
	s->bit_count = 0;
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static t_server	s;

	(void)context;
	if (s.client_pid == 0 || s.client_pid != info->si_pid)
		init_server(&s, info->si_pid);
	s.current_char = (s.current_char << 1) | (sig == SIGUSR2);
	s.bit_count++;
	if (s.bit_count == 8)
		handle_char(&s);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1)
	{
		ft_putstr_fd("Error: Signal setup failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
