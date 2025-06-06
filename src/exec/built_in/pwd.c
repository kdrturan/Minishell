/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:09:06 by abturan           #+#    #+#             */
/*   Updated: 2025/06/04 16:37:14 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<exec.h>

void    pwd(t_shell *shell, t_cmd *cmd)
{
    printf("%s\n", (char *)gc_track(&shell->gc, getcwd(NULL, 0)));
}
