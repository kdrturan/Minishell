/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:32:10 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/27 21:06:55 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	execute_pipeline(t_shell *shell)
{
	t_cmd	*commands;
	int		pipe_fd[2];
	int		prev_fd;
	int		flag;

	flag = 1;
	prev_fd = -1;
	commands = shell->cmd_list;
	while (commands)
	{
		if (commands->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		if (!shell->cmd_list->next && is_builtin(commands))
		{
			manage_redir(commands);
			flag = builtin_functions(shell, commands);
		}
		else
			commands->pid = fork();
		if (flag && commands->pid == 0)
			child_process(prev_fd, shell, commands, pipe_fd);
		else
			main_process(&prev_fd, commands, pipe_fd);
		commands = commands->next;
	}
	if (shell->cmd_list && shell->cmd_list->pid)
		wait_childs(shell);
}
