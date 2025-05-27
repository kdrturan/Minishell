/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:45:42 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 22:25:44 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_shell(t_shell **shell, char **env_data)
{
	(*shell) = malloc(sizeof(t_shell));
	if (!shell)
		return ;
	(*shell)->env = env_parse(env_data);
}
