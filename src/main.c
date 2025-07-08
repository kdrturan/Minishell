/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/08 21:28:03 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>
#include <env.h>
#include <exec.h>
#include <gc.h>
#include <init.h>
#include <lexer.h>
#include <minishell.h>
#include <parser.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <token.h>
#include <utils.h>

int	main(int ac, char **av, char **env_data)
{
	t_shell	shell;

	(void)av;
	(void)ac;
	gc_init(&shell);
	init_shell(&shell, env_data);
	while (1)
	{
		shell.input = gc_track(&shell.gc, ft_strtrim(gc_track(&shell.gc,
					readline(get_prompt(shell.exit_status))), WHITESPACES));
		if (shell.input == NULL)
			break ;
		lexer_run(&shell);
		parser_run(&shell);
		add_history(shell.input);
		//debug_print_cmd_list(shell.cmd_list);
		if (shell.exit_status == 2)
		{
			print_error(false, NULL, NULL, E_SYNTAX);
			token_clean(&shell.token_list);
			cmd_clean(&shell.cmd_list);
			gc_free_all(&shell.gc);
			continue ;
		}
		if (exec(&shell))
			break ;
		set_signals(S_MAIN);
		token_clean(&shell.token_list);
		cmd_clean(&shell.cmd_list);
		gc_free_all(&shell.gc);
	}
	gc_free_all(&shell.env_gc);
	return (0);
}

