/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 18:22:22 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>
#include <init.h>
#include <parser.h>
#include <env.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **env_data)
{
	t_shell *shell;

	init_shell(&shell, env_data);
	
	while (1)
	{
		shell->cmd = readline("MINISHELL>");
		if (shell->cmd == NULL)
			exit (0);
		parse(shell);
		free(shell->cmd);
	}
	return (0);
}
