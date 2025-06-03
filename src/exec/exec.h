/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:37:18 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/03 18:12:09 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <minishell.h>
#include <parser.h>
#include <libft.h>
#include <env.h>

void	exec(t_shell *shell);
void	env(t_shell *shell);
void	export(t_shell *shell, t_cmd *cmd);
void	unset(t_shell *shell, t_cmd *cmd);

#endif
