/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:19:40 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 18:24:46 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

void	debug_env_print(t_env *env)
{
	size_t	i;

	if (!env)
	{
		printf("env is NULL\n");
		return ;
	}
	printf("Environment variables (%zu):\n", env->count);
	for (i = 0; i < env->count; i++)
	{
		printf("[%zu] %s=%s\n", i, env->pairs[i].key, env->pairs[i].val);
	}
}