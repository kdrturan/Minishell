/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:53:36 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/04 16:36:31 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	export(t_shell *shell, t_cmd *cmd)
{
	char	**arg;

	arg = NULL;
	if (cmd->args[1])
	{
		arg = (char **)gc_track_array(&shell->gc, (void **)ft_split(cmd->args[1], '='));
		if (!arg)
			return ;
		env_set(shell, arg[0], arg[1]);
	}
}
