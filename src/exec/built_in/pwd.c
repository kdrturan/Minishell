/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:09:06 by abturan           #+#    #+#             */
/*   Updated: 2025/07/09 03:04:37 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	pwd(t_shell *shell, t_cmd *cmd)
{
	(void)cmd;
	printf("%s\n", (char *)gc_track(&shell->gc, getcwd(NULL, 0)));
	shell->exit_status = 0;
}
