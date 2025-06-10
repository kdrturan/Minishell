/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:27 by abturan           #+#    #+#             */
/*   Updated: 2025/06/04 01:43:58 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<exec.h>

void    echo(t_shell *shell,t_cmd *cmd)
{
    size_t i;
    int flag;

    flag = 0;
    i = 1;
    while (cmd->args[i])
    {
        if (!ft_strncmp(cmd->args[i], "-n", 3))
            flag = 1;
        else
            printf("%s ",cmd->args[i]);
        i++;
    }
    if (flag == 0)   
        printf("\n");
}