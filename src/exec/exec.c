/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:36:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/04 19:09:51 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <unistd.h>

int	exec(t_shell *shell)
{
	t_cmd *cmds;

	cmds = shell->cmd_list; 
	execute_pipeline(shell);
	while (cmds)
	{
		if (cmds->status == 127)
		{
			ft_putstr_fd (cmds->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		cmds = cmds->next;
	}
	return (0);
}
