/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:36:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/13 23:35:25 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <unistd.h>

void	exec(t_shell *shell)
{
	execute_pipeline(shell);
	if (access(".temp_heredoc", F_OK) != -1)
		unlink(".temp_heredoc");
	exit_code(0);
}
