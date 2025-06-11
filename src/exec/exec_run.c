/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:35:19 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/11 16:35:58 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

int	builtin_functions(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0])))
		env(shell);
	else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])))
		export(shell, cmd);
	else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])))
		unset(shell, cmd);
	else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])))
		pwd(shell, cmd);
	else if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])))
		echo(shell, cmd);
	else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0])))
		cd(shell, cmd);
	else
		return (1);
	return (0);
}

void	cmd_run(t_shell *shell, t_cmd *cmd)
{
	char	**env;
	char	*full_path;
	int		execve_val;

	env = env_cast_char(shell);
	full_path = find_in_path(shell, cmd);
	if (full_path)
	{
		execve_val = execve(full_path, cmd->args, env);
		if (execve_val == -1)
		{
			perror("command not found");
			exit(127);
		}
	}
	perror("command not found");
}

char	*find_in_path(t_shell *shell, t_cmd *cmd)
{
	int is_exist;
	char **full_path;
	char *path;
	size_t i;

	i = 0;
	path = env_get_value(shell, "PATH");
	full_path = ft_split(path, ':');
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