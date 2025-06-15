/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:27 by abturan           #+#    #+#             */
/*   Updated: 2025/06/11 20:01:02 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<exec.h>

void    echo(t_cmd *cmd)
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