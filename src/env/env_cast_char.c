/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cast_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 03:58:37 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 03:58:43 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

char	**env_cast_char(t_shell *shell)
{
	size_t	i;
	char	**value;
	char	*temp;

	i = 0;
	value = NULL;
	value = gc_track(&shell->exec_gc, malloc(sizeof(char *)
				* (shell->env->count + 1)));
	while (i < shell->env->count)
	{
		temp = gc_track(&shell->exec_gc, ft_strjoin(shell->env->pairs[i].key,
					"="));
		if (shell->env->pairs[i].val)
			value[i] = gc_track(&shell->exec_gc, ft_strjoin(temp,
						shell->env->pairs[i].val));
		else
			value[i] = temp;
		i++;
	}
	value[i] = NULL;
	return (value);
}
