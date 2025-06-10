/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cast_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:30:59 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/10 15:17:13 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

char **env_cast_char(t_shell *shell)
{
	size_t i;
	char **value;
	char *temp;

	i = 0;
	value = gc_track(&shell->gc, malloc(sizeof(char *) * (shell->env->count + 1)));
	while (i < shell->env->count)
	{
		temp = ft_strjoin(shell->env->pairs[i].key, "=");
		if (shell->env->pairs[i].val)
			value[i] = gc_track(&shell->gc, ft_strjoin(temp, shell->env->pairs[i].val));
		else
			value[i] = temp;
		free(temp);
		i++;
	}
	value[i] = NULL;
	return (value);
}
