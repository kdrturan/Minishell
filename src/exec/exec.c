/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:36:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/29 16:19:07 by tuaydin          ###   ########.fr       */
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
