/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:37:40 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:02:54 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

size_t	env_len(char **env, t_pair *pairs)
{
	size_t	i;

	i = 0;
	if (pairs)
		return (i);
	if (env && *env)
	{
		while (env[i])
			i++;
	}
	return (i);
}
