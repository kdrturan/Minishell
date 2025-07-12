/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/12 23:06:45 by abturan          ###   ########.fr       */
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

static void	main_loop(t_shell *shell)
{
	shell->cmd_status = 0;
	shell->input = gc_track(&shell->gc, ft_strtrim(gc_track(&shell->gc,
					readline(get_prompt(shell->exit_status))), WHITESPACES));
	if (!shell->input)
	{
		ft_exit(shell, NULL);
		return ;
	}
	lexer_run(shell);
	parser_run(shell);
	add_history(shell->input);
	if (shell->cmd_status == 2)
	{
		token_clean(&shell->token_list);
		cmd_clean(&shell->cmd_list);
		gc_free_all(&shell->gc);
		return ;
	}
	exec(shell);
	set_signals(S_MAIN);
	token_clean(&shell->token_list);
	cmd_clean(&shell->cmd_list);
	gc_free_all(&shell->gc);
}

int	main(int ac, char **av, char **env_data)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	gc_init(&shell);
	init_shell(&shell, env_data);
	while (1)
		main_loop(&shell);
	gc_free_all(&shell.env_gc);
	return (0);
}
