/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:36:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/04 02:03:44 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	exec(t_shell *shell)
{
	t_cmd   *cmds;

	cmds = shell->cmd_list;
	while (cmds)
	{
		printf("[child] pid: %d\n", getpid());
		if (!ft_strncmp("env", cmds->args[0], ft_strlen(cmds->args[0]) + 1))
			env(shell);
		else if (!ft_strncmp("export", cmds->args[0], ft_strlen(cmds->args[0] + 1)))
			export(shell, cmds);
		else if (!ft_strncmp("unset", cmds->args[0], ft_strlen(cmds->args[0] + 1)))
			unset(shell, cmds);
		else if (!ft_strncmp("pwd", cmds->args[0], ft_strlen(cmds->args[0] + 1)))
			pwd(shell, cmds);
		else if (!ft_strncmp("echo", cmds->args[0], ft_strlen(cmds->args[0] + 1)))
			echo(shell, cmds);
		else if (!ft_strncmp("cd", cmds->args[0], ft_strlen(cmds->args[0] + 1)))
			cd(shell, cmds);
		cmds = cmds->next;
	}    
}
