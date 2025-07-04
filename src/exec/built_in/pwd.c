/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:09:06 by abturan           #+#    #+#             */
/*   Updated: 2025/07/04 15:42:36 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	pwd(t_shell *shell, t_cmd *cmd)
{
	(void)cmd;
	printf("%s\n", (char *)gc_track(&shell->gc, getcwd(NULL, 0)));
}
