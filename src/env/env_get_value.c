/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:54:37 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/03 14:15:47 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

char	*env_get_value(t_shell *shell, char *key)
{
	size_t	i;

	i = 0;
	if (!key)
		return (gc_track(&shell->gc, ft_strdup("")));
	while (i < shell->env->count)
	{
		if (ft_strncmp(shell->env->pairs[i].key, key, ft_strlen(key) + 1) == 0)
			return (shell->env->pairs[i].val);
		i++;
	}
	return (gc_track(&shell->gc, ft_strdup("")));
}
