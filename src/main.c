/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/03 05:19:25 by tuaydin          ###   ########.fr       */
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
#include <utils.h>
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
		shell.input = ft_strtrim(gc_track(&shell.gc, readline(PROMPT)), 
				WHITESPACES);
		if (shell.input == NULL)
			break ;
		add_history(shell.input);
		if (!validate_input(shell.input))
		{
			printf("invalid input\n");
			free(shell.input);
			continue;
		}
		lexer_run(&shell);
		parser_run(&shell);
		debug_print_cmd_list(shell.cmd_list);
		// execution func.
		token_clean(&shell.token_list);
		cmd_clean(&shell.cmd_list);
		free(shell.input);
	}
	gc_free_all(&shell.gc);
	return (0);
}
