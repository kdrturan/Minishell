/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:27 by abturan           #+#    #+#             */
/*   Updated: 2025/07/07 01:35:33 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	echo(t_shell *shell, t_cmd *cmd)
{
	size_t	i;
	int		flag;

	flag = 0;
	i = 0;
	while (cmd && cmd->args && cmd->args[1] && cmd->args[1][i])
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
	free(shell->input);
	gc_free_all(&shell->gc);
	gc_free_all(&shell->env_gc);
	exit(0);
}
