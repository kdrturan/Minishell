/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:37:18 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/10 17:56:52 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <minishell.h>
# include <parser.h>
# include <libft.h>
# include <env.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

void	exec(t_shell *shell);
void	env(t_shell *shell);
void	export(t_shell *shell, t_cmd *cmd);
void	unset(t_shell *shell, t_cmd *cmd);
void	pwd(t_shell *shell, t_cmd *cmd);
void	echo(t_shell *shell,t_cmd *cmd);
void	cd(t_shell *shell, t_cmd *cmd);
void execute_pipeline(t_shell *shell);
char *find_in_path(t_shell *shell,t_cmd *cmd);
void	main_process(int *prev_fd, t_shell *shell, t_cmd *cmd, int *pipe_fd);
void	wait_childs(t_shell *shell);
int builtin_functions(t_shell *shell, t_cmd *cmd);

#endif
