/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:37:18 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/13 23:32:30 by abturan          ###   ########.fr       */
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
# include <signal.h>
# include <signal_handler.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_exec
{
	t_cmd	*commands;
	int		pipe_fd[2];
	int		prev_fd;
	int		flag;
}			t_exec;

void			exec(t_shell *shell);
void		env(t_shell *shell, t_cmd *cmd);
void		export(t_shell *shell, t_cmd *cmd);
void		unset(t_shell *shell, t_cmd *cmd);
void		pwd(t_shell *shell, t_cmd *cmd);
void		echo(t_shell *shell, t_cmd *cmd);
void		cd(t_shell *shell, t_cmd *cmd);
void		execute_pipeline(t_shell *shell);
char		*find_in_path(t_shell *shell, t_cmd *cmd);
void		main_process(int *prev_fd, t_cmd *cmd, int *pipe_fd);
void		wait_childs(t_shell *shell);
int			builtin_functions(t_shell *shell, t_cmd *cmd);
void		manage_redir(t_shell *shell, t_redir *redir);
int			is_builtin(t_cmd *cmd);
void		manage_redir_main(t_shell *shell, t_redir *redir);
void		ft_exit(t_shell *shell, t_cmd *cmd);
void		file_heredoc(t_shell *shell, t_redir *redirs);
void		handle_heredoc(t_shell *shell);
void		pre_check(char *cmd, int *status);
void		pre_check_part(struct stat st, char *cmd, int *status);
void		handle_error(t_cmd *cmd, int *status);
#endif
