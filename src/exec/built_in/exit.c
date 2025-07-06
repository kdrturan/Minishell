/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:54:49 by abturan           #+#    #+#             */
/*   Updated: 2025/07/07 00:04:05 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static int check_error(t_shell *shell, t_cmd *cmd)
{
    size_t  i;

    i = 0;
    if (cmd && cmd->args && cmd->args[1])
    {
        while (cmd->args[1][i])
        {
            if (!ft_isnumeric(cmd->args[1]))
            {
                print_error(true, cmd->args[0], cmd->args[1], E_ARG1);
                return (2);
            }
            i++;
        }  
        if (cmd->args[2])
        {
            print_error(true, cmd->args[0], cmd->args[1], E_ARG0);
            return (1);
        }
    }
    return (0);
}

void    ft_exit(t_shell *shell, t_cmd *cmd)
{
    int value;

    value = check_error(shell, cmd);
    if (!value && cmd->args[1])
        value = ft_atoi(shell->cmd_list->args[1]);
    free(shell->input);
    gc_free_all(&shell->gc);
    gc_free_all(&shell->env_gc);
    gc_free_all(&shell->exec_gc);
    exit(value);
}
