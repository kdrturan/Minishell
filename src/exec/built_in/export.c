/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:53:36 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/04 18:24:03 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static bool checkError(t_shell *shell, t_cmd *cmd)
{
	if (cmd && cmd->args && cmd->args[1])
	{
		if (access(cmd->args[1], F_OK) == 0)
		{
			ft_putstr_fd("export: ", STDERR_FILENO);
			ft_putstr_fd("‘", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd("’", STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			shell->exit_status = 1;
			return (true);
		}
	}
	return (false);
}

void	export(t_shell *shell, t_cmd *cmd)
{
	char	**arg;
	size_t	i;

	i = 0;
	arg = NULL;
	if (checkError(shell, cmd))
		return ;
	if (cmd->args[1])
	{
		arg = (char **)gc_track_array(&shell->env_gc,
				(void **)ft_split(cmd->args[1], '='));
		if (!arg)
			return ;
		if (ft_strchr(cmd->args[1], '=') && arg && !arg[1])
			arg[1] = gc_track(&shell->env_gc, ft_strdup(""));
		env_set(shell, arg[0], arg[1]);
	}
	else
	{
		while (i < shell->env->count)
		{
			printf("declare -x %s", shell->env->pairs[i].key);
			if (shell->env->pairs[i].val)
				printf("=\"%s\"", shell->env->pairs[i].val);
			printf("\n");
			i++;
		}
	}
}
