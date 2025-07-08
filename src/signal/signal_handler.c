/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:57 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/08 23:17:19 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handler.h>
#include <sys/ioctl.h>

static void	signal_handler(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

static void	heredoc(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("^C\n", 1);
	exit(130);
}

void	set_signals(t_mode mode)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (mode == S_MAIN)
	{
		sa.sa_handler = signal_handler;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == S_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == S_HEREDOC)
	{
		sa.sa_handler = heredoc;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
