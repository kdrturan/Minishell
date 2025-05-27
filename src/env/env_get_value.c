/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:54:37 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 23:13:21 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_get_value(t_env *env, char *key)
{
    size_t  i;

    i = 0;
    while (i < env->count)
    {
        if (ft_strncmp(env->pairs[i].key, key, ft_strlen(key)) == 0)
            return (env->pairs[i].val);
        i++;
    }
    return (NULL);
}
