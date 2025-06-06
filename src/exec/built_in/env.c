/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:41:22 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/04 01:56:28 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	env(t_shell *shell)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		size_t	i;

		i = 0;
		while (i < shell->env->count)
		{
			printf("%s=%s\n", shell->env->pairs[i].key, shell->env->pairs[i].val);
			i++;
		}
	}
	
}
