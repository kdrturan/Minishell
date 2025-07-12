/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:57:20 by abturan           #+#    #+#             */
/*   Updated: 2025/07/12 23:04:25 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	heredoc_error_handler(t_shell *shell, char *tmp)
{
	gc_free_all(&shell->gc);
	gc_free_all(&shell->env_gc);
	gc_free_all(&shell->exec_gc);
	free(tmp);
	exit(130);
}

void	heredoc_loop(t_shell *shell, t_redir *redir, int flag, int *pipefd)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (exit_code(-1) == 130)
			heredoc_error_handler(shell, tmp);
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
