/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:35:54 by kskender          #+#    #+#             */
/*   Updated: 2025/07/14 11:19:58 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	write(1, "A", 1);
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
	timeout = 10;
	while (!g_ack_received && timeout-- > 0)
		usleep(100);
	if (timeout <= 0)
	{
		ft_putstr_fd("Errror:No ACK received\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	send_char(pid_t pid, char c)
{
	int	i;

	i = 8;
	while (i--)
		send_bit(pid, (c >> i) & 1);
}

void	send_numbs_of_chars(char *msg, pid_t pid)
{
	unsigned long	num;
	long			i;

	i = 63;
	num = ft_strlen(msg) + 1;
	while (i >= 0)
	{
		send_bit(pid, (num >> i) & 1);
		i--;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				pid;

	if (ac != 3)
	{
		ft_putstr_fd("Usage: ./client [PID] [MESSAGE]\n", STDERR_FILENO);
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
		return (ft_putstr_fd("Error: SIGUSR1 setup failed\n", 2), 2);
	send_numbs_of_chars(av[2], pid);
	while (*av[2])
		send_char(pid, *av[2]++);
	return (send_char(pid, '\0'), 0);
}
