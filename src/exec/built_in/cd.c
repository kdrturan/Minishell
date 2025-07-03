/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:23 by abturan           #+#    #+#             */
/*   Updated: 2025/07/03 18:18:54 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*buff;
	char	*tmp;

	tmp = *cmd->args;
	if (cmd->args[1] == NULL)
	{
		chdir(env_get_value(shell, "HOME"));
		env_set(shell, "OLDPWD", env_get_value(shell, "PWD"));
		env_set(shell, "PWD", env_get_value(shell, "HOME"));
		return ;
	}
	if (chdir(cmd->args[1]) == -1)
		return ;
	buff = gc_track(&shell->gc, getcwd(NULL, 0));
	if (buff != NULL)
	{
		env_set(shell, "PWD", buff);
		env_set(shell, "OLDPWD", tmp);
	}
}
