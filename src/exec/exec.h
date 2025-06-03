/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:12:29 by abturan           #+#    #+#             */
/*   Updated: 2025/06/03 19:22:28 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef EXEC_H
# define EXEC_H

# include<stdio.h>
# include<minishell.h>
# include<parser.h>
#include <unistd.h>

void    echo(t_shell *shell,t_cmd *cmd);
void cd(t_shell *shell, t_cmd *cmd);

#endif