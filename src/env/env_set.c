/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:50:34 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <libft.h>
#include <string.h>

void	env_set(t_shell *shell, char *key, char *val)
{
	size_t	i;

	i = 0;
	while (i < shell->env->count)
	{
		if (ft_strncmp(shell->env->pairs[i].key, key, ft_strlen(key) + 1) == 0)
		{
			shell->env->pairs[i].val = val;
			return ;
		}
		i++;
	}
	env_add(shell, key, val);
}
