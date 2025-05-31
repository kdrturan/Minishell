/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:19:40 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 14:12:50 by kdrturan         ###   ########.fr       */
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
	i = 0;
	while (i < env->count)
	{
		printf("[%zu] %s=%s\n", i, env->pairs[i].key, env->pairs[i].val);
		i++;
	}
}
