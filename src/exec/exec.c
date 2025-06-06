/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:36:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/04 16:33:34 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	exec(t_shell *shell)
{
	t_cmd	*cmds;

	cmds = shell->cmd_list;
	while (cmds)
	{
		if (!cmds->args || !cmds->args[0])
		{
			cmds = cmds->next;
			continue;
		}
		if (!ft_strncmp("env", cmds->args[0], ft_strlen(cmds->args[0])))
			env(shell);
		else if (!ft_strncmp("export", cmds->args[0], ft_strlen(cmds->args[0])))
			export(shell, cmds);
		else if (!ft_strncmp("unset", cmds->args[0], ft_strlen(cmds->args[0])))
			unset(shell, cmds);
		else if (!ft_strncmp("pwd", cmds->args[0], ft_strlen(cmds->args[0])))
			pwd(shell, cmds);
		else if (!ft_strncmp("echo", cmds->args[0], ft_strlen(cmds->args[0])))
			echo(shell, cmds);
		else if (!ft_strncmp("cd", cmds->args[0], ft_strlen(cmds->args[0])))
			cd(shell, cmds);
		cmds = cmds->next;
	}
}
