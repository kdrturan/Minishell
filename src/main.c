/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:38:47 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <init.h>
#include <gc.h>
#include <readline/history.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **env_data)
{
	t_shell shell;

	gc_init(&shell.gc);
	init_shell(&shell, env_data);
	
	while (1)
	{
		shell.cmd = readline("MINISHELL>");
		if (shell.cmd == NULL)
			break ;
		parse(&shell);
		free(shell.cmd);
	}

	gc_free_all(&shell.gc);
	return (0);
}
