/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:46:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/13 02:18:57 by tuaydin          ###   ########.fr       */
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
