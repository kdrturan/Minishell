/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:57:56 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:37:45 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <gc.h>
#include <libft.h>

t_env	*env_parse(t_shell *shell, char **env_data)
{
	t_env	*env;
	size_t	i;
    char **values;

    env = gc_malloc(&shell->gc, sizeof(t_env));
	env->count = env_len(env_data, NULL);
	env->pairs = gc_malloc(&shell->gc, sizeof(t_pair) * env->count);
    i = 0;
	while (env_data[i])
	{
        values = gc_track_array(&shell->gc, ft_split(env_data[i], '='));
        env->pairs[i].key = values[0];
		env->pairs[i].val = values[1];
		i++;
	}
    return (env);
}
