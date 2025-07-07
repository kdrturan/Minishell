/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:38:54 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/07 05:38:08 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parser_run(t_shell *shell)
{
	parse_preprocess(shell);
	generate_commands(shell);
	check_syntax(shell);
}
