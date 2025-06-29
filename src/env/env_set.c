/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/29 18:35:02 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	env_set(t_shell *shell, char *key, char *val)
{
	size_t	i;

	i = 0;
	while (i < shell->env->count)
	{
		if (ft_strncmp(shell->env->pairs[i].key, key, ft_strlen(key) + 1) == 0)
		{
			shell->env->pairs[i].val = gc_track(&shell->env_gc, ft_strdup(val));
			return ;
		}
		i++;
	}
	env_add(shell, key, val);
}
