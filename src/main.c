/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 20:23:05 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <init.h>
#include <gc.h>
#include <lexer.h>
#include <token.h>
#include <env.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **env_data)
{
	t_shell	shell;

	(void) av;
	(void) ac;
	gc_init(&shell.gc);
	init_shell(&shell, env_data);
	while (1)
	{
		shell.cmd = readline(PROMPT);
		if (shell.cmd == NULL)
			break ;
		add_history(shell.cmd);
		lexer_run(&shell);
		//parser func.
		//execution func.
		token_clean(&shell.token_list);
		free(shell.cmd);
	}
	gc_free_all(&shell.gc);
	return (0);
}
