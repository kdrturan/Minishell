/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:57:56 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 18:16:59 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

t_env	*env_parse(char **env_data)
{
	t_env	*env;
	size_t	i;
    char **values;

    env = malloc(sizeof(t_env));
	env->count = env_len(env_data, NULL);
	env->pairs = malloc(sizeof(t_pair) * env->count);
    i = 0;
	while (env_data[i])
	{
        values = ft_split(env_data[i], '=');
        env->pairs[i].key = values[0];
		env->pairs[i].val = values[1];
		i++;
	}
    return (env);
}
