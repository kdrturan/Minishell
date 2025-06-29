/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:53:36 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/29 17:17:32 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	export(t_shell *shell, t_cmd *cmd)
{
	char	**arg;
	size_t	i;

	i = 0;
	arg = NULL;
	if (cmd->args[1])
	{
		arg = (char **)gc_track_array(&shell->gc, (void **)ft_split(cmd->args[1], '='));
		if (!arg)
		return ;
		if (ft_strchr(cmd->args[1], '=') && arg && !arg[1])
			arg[1] = gc_track(&shell->gc, ft_strdup(""));
		env_set(shell, arg[0], arg[1]);
	}
	else
		while (i < shell->env->count)
		{
			printf("declare -x %s", shell->env->pairs[i].key);
			if (shell->env->pairs[i].val)
				printf("=\"%s\"", shell->env->pairs[i].val);
			printf("\n");
			i++;
		}
}
