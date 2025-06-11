/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:51:09 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/11 16:35:54 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	manage_redir(t_cmd *cmd)
{
	int	fd;

	while (cmd->redir)
	{
		if (cmd->redir->type == OUTPUT || cmd->redir->type == APPEND)
		{
			if (cmd->redir->type == APPEND)
				fd = open(cmd->redir->target, O_CREAT | O_WRONLY | O_APPEND,
						0644);
			else
				fd = open(cmd->redir->target, O_CREAT | O_WRONLY | O_TRUNC,
						0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (cmd->redir->type == INPUT)
		{
			fd = open(cmd->redir->target, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		if (cmd->redir->type == HEREDOC)
			handle_heredoc(cmd);
		else
			close(fd);
		cmd->redir = cmd->redir->next;
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	char	*tmp;
	int		pipefd[2];

	pipe(pipefd);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strncmp(tmp, cmd->redir->target,
				ft_strlen(cmd->redir->target) + 1))
		{
			free(tmp);
			break ;
		}
		write(pipefd[1], tmp, ft_strlen(tmp));
		write(pipefd[1], "\n", 1);
		free(tmp);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
