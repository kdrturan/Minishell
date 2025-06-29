/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/29 16:21:56 by tuaydin          ###   ########.fr       */
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
	gc_init(&shell.gc, &shell.exec_gc);
	init_shell(&shell, env_data);
	while (1)
	{
		shell.input = ft_strtrim(gc_track(&shell.gc,
					readline(get_prompt(shell.exit_status))), WHITESPACES);
		if (shell.input == NULL)
			break ;
		add_history(shell.input);
		if (!validate_input(&shell, shell.input))
		{
			ft_putendl_fd("syntax error", STDERR_FILENO);
			free(shell.input);
			continue ;
		}
		lexer_run(&shell);
		parser_run(&shell);
		debug_print_cmd_list(shell.cmd_list);
		if (exec(&shell))
			break ;
		token_clean(&shell.token_list);
		cmd_clean(&shell.cmd_list);
		free(shell.input);
	}
	gc_free_all(&shell.gc);
	return (0);
}
