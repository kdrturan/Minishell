/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 02:53:47 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "signal_handler.h"

int	main(int ac, char **av, char **env)
{
	set_signals(INTERACTIVE);

	char *temp;
	while (1)
	{
		temp = readline("MINISHELL>");
		if (temp == NULL)
			exit (0);
		printf("%s\n",temp);
		free(temp);
	}
	return (0);
}
