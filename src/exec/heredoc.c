/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:57:20 by abturan           #+#    #+#             */
/*   Updated: 2025/07/13 23:34:43 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	file_heredoc(t_shell *shell, t_redir *redirs)
{
	int		fd;
	char	*tmpstr;
	char	*tmp;

	tmpstr = NULL;
	fd = open(".temp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	write(fd, tmpstr, ft_strlen(tmpstr));
	tmpstr = NULL;
	redirs->target = ".temp_heredoc";
	redirs->type = INPUT;
	redirs = redirs->next;
}

void	handle_heredoc(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	t_redir	*redirs;

	set_signals(S_HEREDOC);
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
			file_heredoc(shell, redirs);
		}
		tmp_cmd = tmp_cmd->next;
	}
	if (exit_code(-1) == 130)
	{
		shell->exit_status = 130;
		open("/dev/tty", O_RDONLY);
	}
	set_signals(S_MAIN);
}
