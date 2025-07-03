/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:51:09 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/03 18:19:41 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	manage_redir(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == OUTPUT || redir->type == APPEND)
		{
			if (redir->type == APPEND)
				fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (redir->type == INPUT)
		{
			fd = open(redir->target, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		if (redir->type == HEREDOC)
			handle_heredoc(redir);
		else
			close(fd);
		redir = redir->next;
	}
}

void	handle_heredoc(t_redir *redir)
{
	char	*tmp;
	int		pipefd[2];
	t_redir	*redirtmp;
	int		flag;

	flag = 1;
	redirtmp = redir;
	pipe(pipefd);
	while (redirtmp)
	{
		redirtmp = redirtmp->next;
		if (redirtmp && redirtmp->type == HEREDOC)
			flag = 0;
	}
	while (1)
	{
		tmp = readline("> ");
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
	if (flag)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}
