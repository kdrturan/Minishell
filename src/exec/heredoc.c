/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:57:20 by abturan           #+#    #+#             */
/*   Updated: 2025/07/13 02:20:43 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	heredoc_loop(t_shell *shell, t_redir *redir, int flag, int *pipefd)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (exit_code(-1) == 130)
		{
			shell->exit_status = 130;
			gc_track(&shell->gc, tmp);
			c_exit(shell);
		}
		if (!tmp || !ft_strncmp(tmp, redir->target, ft_strlen(redir->target)
				+ 1))
		{
			free(tmp);
			break ;
		}
		if (flag)
		{
			write(pipefd[1], tmp, ft_strlen(tmp));
			write(pipefd[1], "\n", 1);
		}
		free(tmp);
	}
}

void	handle_heredoc(t_shell *shell, t_redir *redir)
{
	int		pipefd[2];
	t_redir	*redirtmp;
	int		flag;

	(void)shell;
	set_signals(S_HEREDOC);
	flag = 1;
	redirtmp = redir;
	pipe(pipefd);
	while (redirtmp)
	{
		redirtmp = redirtmp->next;
		if (redirtmp && redirtmp->type == HEREDOC)
			flag = 0;
	}
	heredoc_loop(shell, redir, flag, pipefd);
	if (flag)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}
