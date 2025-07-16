/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:47:05 by kskender          #+#    #+#             */
/*   Updated: 2025/07/14 20:47:23 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;
volatile sig_atomic_t	g_message_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	message_ack_handler(int sig)
{
	(void)sig;
	g_message_ack = 1;
}

static void	send_bit(pid_t pid, int bit)
{
	int	sig;
	int	timeout;

	timeout = 1000;
	sig = (bit) ? SIGUSR2 : SIGUSR1;
	g_ack_received = 0;
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error: Signal send failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (!g_ack_received && timeout-- > 0)
		usleep(1000);
	if (!g_ack_received)
	{
		ft_putstr_fd("Error: No ACK received\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i--)
		send_bit(pid, (c >> i) & 1);
}

void	send_string(unsigned char *msg, pid_t pid)
{
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
		ft_putstr_fd("Usage: ./client_bonus [PID] [MESSAGE]\n", STDERR_FILENO);
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
	sa.sa_handler = message_ack_handler;
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: Signal setup failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	send_string((unsigned char *)av[2], pid);
	while (!g_message_ack)
		pause();
	return (EXIT_SUCCESS);
}
