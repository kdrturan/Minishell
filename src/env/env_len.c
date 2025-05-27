/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:37:40 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 22:03:20 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t  env_len(char **env, t_pair *pairs)
{
    size_t  i;

    i = 0;
    if (pairs)
        ;
    if (env && *env)
    {
        while (env[i])
            i++;
    }
    return (i);
}
