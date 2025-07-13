/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:57 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/13 23:23:54 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal_handler.h>
#include <sys/ioctl.h>
#include <utils.h>
#include <fcntl.h>

static void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit_code(130);
	close(STDIN_FILENO);
}

static void	heredoc(int sig)
{
	(void)sig;
	exit_code(130);
	close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
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
		exit_code(0);
		sa.sa_handler = heredoc;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
