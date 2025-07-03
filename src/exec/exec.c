/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:36:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/03 18:13:47 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <unistd.h>

int	exec(t_shell *shell)
{
	if (shell->cmd_list && shell->cmd_list->args[0]
		&& !ft_strncmp("exit", shell->cmd_list->args[0],
			ft_strlen(shell->cmd_list->args[0]) + 1))
		return (printf("exit\n"), 1);
	execute_pipeline(shell);
	return (0);
}
