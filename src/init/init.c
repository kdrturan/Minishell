/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:45:42 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:34:30 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <env.h>


void	init_shell(t_shell *shell, char **env_data)
{
	if (!shell)
		return ;
	shell->env = env_parse(shell, env_data);
}
