/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:32:10 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/13 22:12:30 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static void	init_exev_var(t_exec *exec_var, t_shell *shell)
{
	exec_var->flag = 1;
	exec_var->prev_fd = -1;
	exec_var->commands = shell->cmd_list;
}

static void	pre_child(t_cmd *commands)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	commands->pid = fork();
}

void	execute_pipeline(t_shell *shell)
{
	t_exec	var;

	init_exev_var(&var, shell);
	handle_heredoc(shell);
	if (exit_code(-1) == 130)
		return ;
	while (var.commands)
	{
		pipe(var.pipe_fd);
		if (!shell->cmd_list->next && is_builtin(var.commands))
		{
			manage_redir_main(shell, var.commands->redir);
			var.flag = builtin_functions(shell, var.commands);
		}
		else
			pre_child(var.commands);
		if (var.flag && var.commands->pid == 0)
			child_process(var.prev_fd, shell, var.commands, var.pipe_fd);
		else
			main_process(&var.prev_fd, var.commands, var.pipe_fd);
		var.commands = var.commands->next;
	}
	if (shell->cmd_list && shell->cmd_list->pid)
		wait_childs(shell);
}
