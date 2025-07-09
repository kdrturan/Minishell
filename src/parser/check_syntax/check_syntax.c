/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 04:31:49 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 03:04:00 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	check_syntax(t_shell *shell)
{
	check_pipes(shell);
	if (shell->exit_status)
		return ;
	check_redirs(shell);
	if (shell->exit_status)
		return ;
}
