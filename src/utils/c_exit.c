/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:46:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/13 21:03:33 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	c_exit(t_shell *shell)
{
	gc_free_all(&shell->gc);
	gc_free_all(&shell->env_gc);
	gc_free_all(&shell->exec_gc);
	exit(shell->exit_status);
}
