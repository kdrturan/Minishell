/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:57:56 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 14:12:20 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

t_env	*env_parse(t_shell *shell, char **env_data)
{
	t_env	*env;
	size_t	i;
	char	**values;

	env = gc_track(&shell->gc, malloc(sizeof(t_env)));
	env->count = env_len(env_data, NULL);
	env->pairs = gc_track(&shell->gc, malloc(sizeof(t_pair) * env->count));
	i = 0;
	while (env_data[i])
	{
		values = (char **)gc_track_array(&shell->gc,
				(void **)ft_split(env_data[i], '='));
		env->pairs[i].key = values[0];
		env->pairs[i].val = values[1];
		i++;
	}
	return (env);
}
