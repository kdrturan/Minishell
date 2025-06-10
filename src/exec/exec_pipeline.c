/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:32:10 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/10 15:39:08 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<exec.h>


void execute_pipeline(t_shell *shell)
{	
	t_cmd* commands;
	int pipe_fd[2];
	int prev_fd;
	
	prev_fd = -1;
	commands = shell->cmd_list;
	while (commands)
	{
		if (commands->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		commands->pid = fork();
		if (commands->pid == 0)
		{
			child_process(prev_fd, shell, commands, pipe_fd);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (commands->next)
			{
				close(pipe_fd[1]); 
				prev_fd = pipe_fd[0]; 
			}
		}
		commands = commands->next;
	}
	
	while (wait(NULL) > 0);
}