/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:35:54 by kskender          #+#    #+#             */
/*   Updated: 2025/07/14 20:40:45 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_bit(pid_t pid, int bit)
{
	int	sig;
	int	timeout;

	if (bit)
		sig = SIGUSR2;
	else
		sig = SIGUSR1;
	g_ack_received = 0;
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error: Signal send failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	timeout = 1000;
	while (!g_ack_received && timeout-- > 0)
		usleep(1000);
	if (!g_ack_received)
	{
		ft_putstr_fd("Error:No ACK received\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	send_char(pid_t pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		send_bit(pid, (c >> i) & 1);
	}
}

void	send_string(char *msg, pid_t pid)
{
	if (!msg)
		return ;
	while (*msg)
		send_char(pid, *msg++);
	send_char(pid, '\0');
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				pid;

	if (ac != 3)
	{
		ft_putstr_fd("How to use: ./client [PID] [MESSAGE]\n", STDERR_FILENO);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 1)
	{
		ft_putstr_fd("Error: Invalid PID\n", STDERR_FILENO);
		return (1);
	}
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: Signal setup failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	send_string(av[2], pid);
	return (EXIT_SUCCESS);
}
