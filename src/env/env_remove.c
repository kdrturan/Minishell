/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:55:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 03:57:04 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

static int	copy_env_except_key(t_shell *sh, t_env *dst, char *key, t_gc *gc)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < sh->env->count)
	{
		if (ft_strncmp(sh->env->pairs[i].key, key, ft_strlen(key) + 1))
		{
			dst->pairs[j].key = gc_track(gc,
					ft_strdup(sh->env->pairs[i].key));
			dst->pairs[j].val = gc_track(gc,
					ft_strdup(sh->env->pairs[i].val));
			if (!dst->pairs[j].key || !dst->pairs[j].val)
				return (0);
			j++;
		}
		i++;
	}
	dst->count = j;
	return (1);
}

t_env	*env_remove(t_shell *shell, char *key, t_gc *gc)
{
	t_env	*dst;

	if (!shell || !key)
		return (NULL);
	dst = gc_track(gc, malloc(sizeof(t_env)));
	if (!dst)
		return (NULL);
	dst->pairs = gc_track(gc,
			malloc(sizeof(t_pair) * shell->env->count));
	if (!dst->pairs)
		return (NULL);
	if (!copy_env_except_key(shell, dst, key, gc))
		return (NULL);
	return (dst);
}
