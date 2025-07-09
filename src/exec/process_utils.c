/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:42:51 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/09 17:32:31 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	wait_childs(t_shell *shell)
{
	t_cmd	*commands;

	commands = shell->cmd_list;
	while (commands)
	{
		if (commands->pid > 0)
			waitpid(commands->pid, &commands->status, 0);
		if ((commands->status & 0x7F) == 0)
			commands->status = (commands->status >> 8) & 0xFF;
		else
		{
			if (commands->status != 13)
				ft_putstr_fd("\n", 1);
			commands->status = 128 + (commands->status & 0x7F);
		}
		shell->exit_status = commands->status;
		commands = commands->next;
	}
}

void	main_process(int *prev_fd, t_cmd *cmd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	child_process(int prev_fd, t_shell *shell, t_cmd *cmd, int *pipe_fd)
{
	set_signals(S_CHILD);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (cmd->redir)
		manage_redir(cmd->redir);
	if (builtin_functions(shell, cmd))
		cmd_run(shell, cmd);
	gc_free_all(&shell->exec_gc);
	exit(0);
}
