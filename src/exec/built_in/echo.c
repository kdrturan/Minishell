/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:27 by abturan           #+#    #+#             */
/*   Updated: 2025/07/04 18:06:57 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	echo(t_cmd *cmd)
{
	size_t	i;
	int		flag;

	flag = 0;
	i = 0;
	while (cmd->args[1][i])
	{
		if (cmd->args[1][i] == '-' && cmd->args[1][++i] && cmd->args[1][i] == 'n')
		{
			while (cmd->args[1][i] == 'n')
				i++;
			if (cmd->args[1][i] == '\0')
				flag = 1;
		}
		i++;
	}
	if (flag)
		i = 2;
	else
		i = 1;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
}
