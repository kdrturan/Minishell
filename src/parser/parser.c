/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:38:54 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/08 21:24:20 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parser_run(t_shell *shell)
{
	complete_pipe(shell);
	parse_preprocess(shell);
	generate_commands(shell);
	check_syntax(shell);
}
