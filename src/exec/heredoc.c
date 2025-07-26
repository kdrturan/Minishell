/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:57:20 by abturan           #+#    #+#             */
/*   Updated: 2025/07/14 02:24:17 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	file_heredoc(t_shell *shell, t_redir *redirs, int *fd)
{
	char	*tmpstr;
	char	*tmp;

	tmpstr = NULL;
	*fd = open(".temp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd == -1)
		return ;
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strncmp(tmp, redirs->target, ft_strlen(redirs->target)
				+ 1))
		{
			free(tmp);
			break ;
		}
		tmpstr = gc_track(&shell->gc, ft_strjoin(tmpstr, tmp));
		tmpstr = gc_track(&shell->gc, ft_strjoin(tmpstr, "\n"));
		free(tmp);
	}
	write(*fd, tmpstr, ft_strlen(tmpstr));
	tmpstr = NULL;
	redirs->target = ".temp_heredoc";
	redirs->type = INPUT;
	redirs = redirs->next;
}

static	void	heredoc_loop(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	t_redir	*redirs;
	int		fd;

	fd = -1;
	tmp_cmd = shell->cmd_list;
	while (tmp_cmd)
	{
		redirs = tmp_cmd->redir;
		while (redirs)
		{
			if (redirs->type != HEREDOC)
			{
				redirs = redirs->next;
				continue ;
			}
			file_heredoc(shell, redirs, &fd);
			if (fd != -1)
				close(fd);
		}
		tmp_cmd = tmp_cmd->next;
	}
}

void	handle_heredoc(t_shell *shell)
{
	set_signals(S_HEREDOC);
	heredoc_loop(shell);
	if (exit_code(-1) == 130)
	{
		shell->exit_status = 130;
		open("/dev/tty", O_RDONLY);
	}
	else
		shell->exit_status = 0;
	set_signals(S_MAIN);
}
