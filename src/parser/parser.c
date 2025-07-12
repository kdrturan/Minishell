/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:38:54 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/12 16:42:36 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parser_run(t_shell *shell)
{
	check_quotes(shell);
	if (shell->cmd_status && shell->token_list == NULL)
		return ;
	parse_preprocess(shell);
	generate_commands(shell);
	check_syntax(shell);
}
