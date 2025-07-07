/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:41:22 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/07 04:28:19 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static bool check_error(t_shell *shell, t_cmd *cmd)
{
	if (cmd && cmd->args && cmd->args[1])
	{
		if (access(cmd->args[1], F_OK) == -1)
		{
			print_error(false, cmd->args[0], cmd->args[1], E_FILE0);
			shell->exit_status = 127;
		}
		else
		{
			print_error(false, cmd->args[0], cmd->args[1], E_PERM0);
			shell->exit_status = 126;
		}
		return (true);
	}
	return (false);
}

void	env(t_shell *shell, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (check_error(shell, cmd))
		return ;
	while (i < shell->env->count)
	{
		if (shell->env->pairs[i].val)
			printf("%s=%s\n", shell->env->pairs[i].key,
				shell->env->pairs[i].val);
		i++;
	}
	shell->exit_status = 0;
}
