/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 16:45:12 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env_data)
{
	t_shell *shell;

	//init_shell(&shell, env_data);
	
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
