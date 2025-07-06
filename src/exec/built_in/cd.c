/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:23 by abturan           #+#    #+#             */
/*   Updated: 2025/07/07 00:03:03 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <errno.h>

static void check_error(t_shell *shell, t_cmd *cmd)
{
	if (cmd && cmd->args && cmd->args[1] && cmd->args[2])
	{
		print_error(true, cmd->args[0], cmd->args[1], E_ARG0);
		shell->exit_status = 1;
		return ;
	}
	if (cmd && cmd->args && cmd->args[1] && chdir(cmd->args[1]) == -1)
	{
		if (errno == ENOENT)
			print_error(true, cmd->args[0], cmd->args[1], E_FILE0);
		else if (errno == ENOTDIR)
			print_error(true, cmd->args[0], cmd->args[1], E_FILE1);
		else if (errno == EACCES)
			print_error(true, cmd->args[0], cmd->args[1], E_PERM0);
	}
	else
		return;
	shell->exit_status = 1;
}

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*buff;
	char	*tmp;
	

	check_error(shell,cmd);
	if (shell->exit_status == 1)
		return ;
	tmp = *cmd->args;
	if (cmd->args[1] == NULL)
	{
		chdir(env_get_value(shell, "HOME"));
		env_set(shell, "OLDPWD", env_get_value(shell, "PWD"));
		env_set(shell, "PWD", env_get_value(shell, "HOME"));
		return ;
	}
	buff = gc_track(&shell->gc, getcwd(NULL, 0));
	if (buff != NULL)
	{
		env_set(shell, "PWD", buff);
		env_set(shell, "OLDPWD", tmp);
	}
}
