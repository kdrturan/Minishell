/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:57 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 20:47:33 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handler.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <libft.h>

static void	signal_handler(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

void	set_signals(t_mode mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (mode == INTERACTIVE)
	{
		sa.sa_handler = signal_handler;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
