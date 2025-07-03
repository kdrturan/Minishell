/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:41:22 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/03 18:19:15 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->env->count)
	{
		if (shell->env->pairs[i].val)
			printf("%s=%s\n", shell->env->pairs[i].key,
				shell->env->pairs[i].val);
		i++;
	}
}
