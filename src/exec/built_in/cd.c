/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:23 by abturan           #+#    #+#             */
/*   Updated: 2025/07/09 02:58:05 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <errno.h>

static void	print_cd_error(t_shell *shell, t_cmd *cmd, char *path)
{
	if (errno == ENOENT)
		print_error(true, cmd->args[0], path, E_FILE0);
	else if (errno == ENOTDIR)
		print_error(true, cmd->args[0], path, E_FILE1);
	else if (errno == EACCES)
		print_error(true, cmd->args[0], path, E_PERM0);
	else
		print_error(true, cmd->args[0], path, E_PERM0);
	shell->exit_status = 1;
}

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;

	shell->exit_status = 0;
	if (cmd->args[1] && cmd->args[2])
	{
		print_error(true, cmd->args[0], NULL, E_ARG0);
		shell->exit_status = 1;
		return ;
	}
	oldpwd = env_get_value(shell, "PWD");
	if (!cmd->args[1] || (cmd->args[1][0] == '~' && cmd->args[1][1] == '\0'))
		target = shell->home_dir;
	else if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
	{
		target = env_get_value(shell, "OLDPWD");
		if (target && target[0] == '\0')
		{
			print_error(true, "cd", NULL, "OLDPWD not set\n");
			shell->exit_status = 1;
			return ;
		}
	}
	else
		target = cmd->args[1];
	if (chdir(target) == -1)
	{
		print_cd_error(shell, cmd, target);
		return ;
	}
	newpwd = gc_track(&shell->gc, getcwd(NULL, 0));
	if (newpwd)
	{
		env_set(shell, "OLDPWD", oldpwd);
		env_set(shell, "PWD", newpwd);
	}
	if (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
		printf("%s\n", newpwd);
}
