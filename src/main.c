/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 20:14:02 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <init.h>
#include <gc.h>
#include <lexer.h>
#include <parser.h>
#include <token.h>
#include <env.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <debug.h>

int	main(int ac, char **av, char **env_data)
{
	t_shell	shell;

	(void)av;
	(void)ac;
	gc_init(&shell.gc);
	init_shell(&shell, env_data);
	while (1)
	{
		shell.cmd = readline(PROMPT);
		shell.cmd = ft_strtrim(shell.cmd, WHITESPACES);
		if (shell.cmd == NULL)
			break ;
		add_history(shell.cmd);
		lexer_run(&shell);
		parser_run(&shell);
		printf("-----TOKENS AFTER PARSE-----\n");
		debug_print_token_list(shell.token_list);
		// execution func.
		token_clean(&shell.token_list);
		free(shell.cmd);
	}
	gc_free_all(&shell.gc);
	return (0);
}
