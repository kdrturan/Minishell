/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:55:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/29 18:53:39 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

t_env	*env_remove(t_shell *shell, char *key, t_gc *gc)
{
	t_env	*dst;
	size_t	i;
	size_t	j;

	if (!shell || !key)
		return (NULL);
	dst = gc_track(gc, malloc(sizeof(t_env)));
	if (!dst)
		return (NULL);
	dst->pairs = gc_track(gc,
			malloc(sizeof(t_pair) * shell->env->count));
	if (!dst->pairs)
		return (NULL);
	i = 0;
	j = 0;
	while (i < shell->env->count)
	{
		if (ft_strncmp(shell->env->pairs[i].key, key,
				ft_strlen(key) + 1))
		{
			dst->pairs[j].key = gc_track(gc,
					ft_strdup(shell->env->pairs[i].key));
			dst->pairs[j].val = gc_track(gc,
					ft_strdup(shell->env->pairs[i].val));
			j++;
		}
		i++;
	}
	dst->count = j;
	return (dst);
}
