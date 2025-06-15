/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:37:18 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/11 20:02:01 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <env.h>
# include <fcntl.h>
# include <libft.h>
# include <minishell.h>
# include <parser.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

void	exec(t_shell *shell);
void	env(t_shell *shell);
void	export(t_shell *shell, t_cmd *cmd);
void	unset(t_shell *shell, t_cmd *cmd);
void	pwd(t_shell *shell);
void	echo(t_cmd *cmd);
void	cd(t_shell *shell, t_cmd *cmd);
void	execute_pipeline(t_shell *shell);
char	*find_in_path(t_shell *shell, t_cmd *cmd);
void	main_process(int *prev_fd, t_cmd *cmd, int *pipe_fd);
void	wait_childs(t_shell *shell);
int		builtin_functions(t_shell *shell, t_cmd *cmd);
void	handle_heredoc(t_cmd *cmd);
void	manage_redir(t_cmd *cmd);

#endif
