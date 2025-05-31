/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 16:53:29 by kdrturan         ###   ########.fr       */
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

int main(int ac, char **av, char **env_data)
{
	t_shell shell;

	(void)av;
	(void)ac;
	gc_init(&shell.gc);
	init_shell(&shell, env_data);
	env_add(&shell, "a", "ls -la");
	while (1)
	{
		shell.cmd = readline(PROMPT);
		shell.cmd = ft_strtrim(shell.cmd, "\t ");
		if (shell.cmd == NULL)
			break;
		add_history(shell.cmd);
		lexer_run(&shell);
		printf("-----TOKENS AFTER LEXER-----\n");
		debug_print_token_list(shell.token_list);
		parser_run(&shell);
		printf("-----TOKENS AFTER PARSER-----\n");
		debug_print_token_list(shell.token_list);
		// execution func.
		token_clean(&shell.token_list);
		free(shell.cmd);
	}
	gc_free_all(&shell.gc);
	return (0);
}
