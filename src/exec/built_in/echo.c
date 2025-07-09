/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:27 by abturan           #+#    #+#             */
/*   Updated: 2025/07/09 04:17:33 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <stdio.h>

static int	is_n_flag(char *arg)
{
	size_t	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

static int	skip_flags(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
		i++;
	return (i);
}

void	echo(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		newline;

	newline = 1;
	if (cmd->args[1] && is_n_flag(cmd->args[1]))
	{
		newline = 0;
		i = skip_flags(cmd);
	}
	else
		i = 1;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	gc_free_all(&shell->gc);
	gc_free_all(&shell->env_gc);
	exit(0);
}
