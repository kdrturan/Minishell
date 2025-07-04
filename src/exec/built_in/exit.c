/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:54:49 by abturan           #+#    #+#             */
/*   Updated: 2025/07/04 19:55:40 by abturan          ###   ########.fr       */
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
                ft_putstr_fd("OIIA OIIA:",2);
                ft_putstr_fd(" exit: ",2);
                ft_putstr_fd(cmd->args[1] ,2);
                ft_putstr_fd(": numeric argument required\n",2);
                return (2);
            }
            i++;
        }  
        if (cmd->args[2])
        {
            ft_putstr_fd("OIIA OIIA:",2);
            ft_putstr_fd(" exit: ",2);
            ft_putstr_fd(cmd->args[1] ,2);
            ft_putstr_fd(": too many arguments\n",2);
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
    gc_free_all(&shell->env_gc);
    exit(value);
}
