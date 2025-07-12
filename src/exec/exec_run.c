/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:35:19 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/13 01:28:25 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <exec.h>
#include <stdio.h>
#include <sys/stat.h>

int	builtin_functions(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[0])
	{
		if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			env(shell, cmd);
		else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])
				+ 1))
			export(shell, cmd);
		else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])
				+ 1))
			unset(shell, cmd);
		else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			pwd(shell, cmd);
		else if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
			echo(shell, cmd);
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

void	handle_error(t_cmd *cmd, int *status)
{
	struct stat	statbuf;

	if (cmd->args && cmd->args[0] && cmd->args[0][0] == '\0')
	{
		print_error(true, cmd->args[0], NULL, E_CMD0);
		*status = 127;
	}
	else if (errno == EACCES)
	{
		if (stat(cmd->args[0], &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
			print_error(true, cmd->args[0], NULL, E_FILE2);
		else
			print_error(true, cmd->args[0], NULL, E_PERM0);
		*status = 126;
	}
	else if (errno == ENOENT)
	{
		print_error(true, cmd->args[0], NULL, E_CMD0);
		*status = 127;
	}
	else
		*status = 1;
}

void	pre_check(char *cmd, int *status)
{
	struct stat	st;

	if (cmd && ft_strchr(cmd, '/'))
	{
		if (cmd && stat(cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				print_error(true, cmd, NULL, E_FILE2);
				*status = 126;
			}
			else if (access(cmd, X_OK) == -1)
			{
				print_error(true, cmd, NULL, E_PERM0);
				*status = 126;
			}
		}
		else
		{
			print_error(true, cmd, NULL, E_FILE0);
			*status = 127;
		}
	}
	else if (cmd && access(cmd, F_OK) == 0)
	{
		print_error(true, cmd, NULL, E_CMD0);
		*status = 127;
	}
	else
		*status = 0;
}

void	cmd_run(t_shell *shell, t_cmd *cmd)
{
	char	**env;
	char	*full_path;

	full_path = NULL;
	pre_check(cmd->args[0], &shell->exit_status);
	env = env_cast_char(shell);
	if (cmd->args[0])
		full_path = find_in_path(shell, cmd);
	if (full_path)
		execve(full_path, cmd->args, env);
	else
		execve(cmd->args[0], cmd->args, env);
	if (!shell->exit_status)
		handle_error(cmd, &shell->exit_status);
	gc_free_all(&shell->gc);
	gc_free_all(&shell->env_gc);
	gc_free_all(&shell->exec_gc);
	exit(shell->exit_status);
}

char	*find_in_path(t_shell *shell, t_cmd *cmd)
{
	int		is_exist;
	char	**full_path;
	char	*path;
	size_t	i;

	i = 0;
	path = env_get_value(shell, "PATH");
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
