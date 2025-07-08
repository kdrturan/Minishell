/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 04:31:49 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/08 23:25:52 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	check_syntax(t_shell *shell)
{
	shell->exit_status = 0;
	check_pipes(shell);
	if (shell->exit_status)
		return ;
	check_redirs(shell);
	if (shell->exit_status)
		return ;
	check_quotes(shell);
	if (shell->exit_status)
		return ;
}
