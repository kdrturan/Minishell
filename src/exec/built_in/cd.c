/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:23 by abturan           #+#    #+#             */
/*   Updated: 2025/07/04 16:26:49 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <errno.h>

static void check_error(t_shell *shell, t_cmd *cmd)
{
	if (chdir(cmd->args[1]) == -1)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("OIIA OIIA",2);
			ft_putstr_fd(" cd: ",2);
			ft_putstr_fd(cmd->args[1] ,2);
			ft_putstr_fd(": No such file or directory.\n",2);
		}
		else if (errno == ENOTDIR)
		{
			ft_putstr_fd("OIIA OIIA",2);
			ft_putstr_fd(" cd: ",2);
			ft_putstr_fd(cmd->args[1],2);
			ft_putstr_fd(": Not a directory.\n",2);
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd("OIIA OIIA",2);
			ft_putstr_fd(" cd: ",2);
			ft_putstr_fd(cmd->args[1],2);
			ft_putstr_fd(": Permission denied.\n",2);
		}
		else 
			return;
	}
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
