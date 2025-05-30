/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:55:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 04:01:12 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <libft.h>

void	env_remove(t_shell *shell, char *key)
{
	t_env	*env;
	t_pair	*new_pairs;
	size_t	i;
	size_t	j;

	env = shell->env;
	new_pairs = gc_track(&shell->gc,
			malloc(sizeof(t_pair) * (env->count - 1)));
	if (!new_pairs)
		return ;
	i = 0;
	j = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->pairs[i].key, key, ft_strlen(key) + 1) != 0)
		{
			new_pairs[j].key = env->pairs[i].key;
			new_pairs[j].val = env->pairs[i].val;
			j++;
		}
		i++;
	}
	env->pairs = new_pairs;
	env->count = j;
}
