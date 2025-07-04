/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:35:19 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/04 21:08:37 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

int	builtin_functions(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[0])
	{
		if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			env(shell, cmd);
		else if (!ft_strncmp("export", cmd->args[0],
				ft_strlen(cmd->args[0]) + 1))
			export(shell, cmd);
		else if (!ft_strncmp("unset", cmd->args[0],
				ft_strlen(cmd->args[0]) + 1))
			unset(shell, cmd);
		else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			pwd(shell, cmd);
		else if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			echo(cmd);
		else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			cd(shell, cmd);
		else if (!ft_strncmp("exit", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			ft_exit(shell, cmd);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

int check(char *path, int status)
{
	struct stat st;

	ft_putstr_fd("OIIA OIIA: ", 2);

	if (stat(path, &st) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (127);
	}

	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("Is a directory\n", 2);
		return (126);
	}

	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return (126);
	}

	if (status == 1)
	{
		ft_putstr_fd("command not found\n", 2);
		return (127);
	}

	return (0); // her şey yolundaysa
}

void	cmd_run(t_shell *shell, t_cmd *cmd)
{
	char	**env;
	char	*full_path;
	int		exit_code;

	full_path = NULL;
	env = (char **)gc_track_array(&shell->exec_gc,
			(void **)env_cast_char(shell));
	if (cmd->args[0])
		full_path = find_in_path(shell, cmd);
	if (full_path)
		shell->exit_status = execve(full_path, cmd->args, env);
	else
		shell->exit_status = execve(cmd->args[0], cmd->args, env);
	exit_code = check(full_path, shell->exit_status);
	exit(exit_code);
}

char	*find_in_path(t_shell *shell, t_cmd *cmd)
{
	int		is_exist;
	char	**full_path;
	char	*path;
	size_t	i;

	i = 0;
	path = gc_track(&shell->exec_gc, env_get_value(shell, "PATH"));
	full_path = (char **)gc_track_array(&shell->exec_gc, (void **)ft_split(path,
				':'));
	while (full_path[i])
	{
		full_path[i] = gc_track(&shell->exec_gc, ft_strjoin(full_path[i], "/"));
		full_path[i] = gc_track(&shell->exec_gc, ft_strjoin(full_path[i],
					cmd->args[0]));
		is_exist = access(full_path[i], F_OK);
		if (!is_exist)
			return (full_path[i]);
		i++;
	}
	return (NULL);
}
