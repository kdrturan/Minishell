/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:41:22 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/04 16:16:08 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static bool check_error(t_shell *shell, t_cmd *cmd)
{
	if (cmd && cmd->args && cmd->args[1])
	{
		if (access(cmd->args[1], F_OK) == -1)
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd("‘", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd("’", STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			shell->exit_status = 127;
		}
		else
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd("‘", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd("’", STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
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
}
