/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:35:19 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/10 15:38:19 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<exec.h>

void	child_process(int prev_fd, t_shell *shell, t_cmd *cmd, int *pipe_fd)
{
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
	cmd_run(shell, cmd);	
}



void cmd_run(t_shell *shell, t_cmd *cmd)
{
	char **environ = env_get_char(shell); 
	char *full_path;
	int		execve_val;
	
	full_path = exec_cmd(shell, cmd);
	if (full_path)
	{
		execve_val = execve(full_path, cmd->args , environ);
		if (execve_val == -1)
		{
			perror("execve failed");
			exit(127);
		}
	}
	exit(1);
}




char *exec_cmd(t_shell *shell,t_cmd *cmd)
{
	int is_exist;
	char **full_path;
	char *path;
	size_t i;

	i = 0;
	path = env_get_value(shell, "PATH");
	full_path = ft_split(path,':');
	while (full_path[i])
	{
		full_path[i] = ft_strjoin(full_path[i], "/");
		full_path[i] = ft_strjoin(full_path[i], cmd->args[0]);
		is_exist = access(full_path[i], F_OK | X_OK);
		if (!is_exist)
		{
			cmd->args[0] = full_path[i];
			return (full_path[i]);
		}
		i++;
	}
	return (NULL);
}