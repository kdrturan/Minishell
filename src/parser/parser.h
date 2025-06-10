/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:21:19 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/10 13:53:39 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h>
# include <token.h>
# include <libft.h>
# include <unistd.h>
# include <utils.h>
# include <env.h>

typedef t_token_type	t_redir_type;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;

struct	s_redir
{
	t_redir_type	type;
	char			*target;
	t_redir			*next;
};

struct	s_cmd
{
	char			**args;
	t_redir			*redir;
	pid_t			pid;
	t_cmd			*next;
};

void	parser_run(
			t_shell *shell);

void	parse_preprocess(
			t_shell *shell);

void	handle_dollar(
			t_shell *shell,
			t_token *dollar);

void	merge_words_br(
			t_shell *shell);

void	merge_words_ar(
			t_shell *shell);

void	generate_commands(
			t_shell *shell);

t_redir	*redir_new(t_shell *shell, t_redir_type type, char *target);
t_redir	*redir_last(t_redir *redir_list);
void	redir_add_back(t_redir **redir_list, t_redir *redir);

t_cmd	*cmd_new(t_shell *shell, char **args, t_redir *redir);
t_cmd	*cmd_last(t_cmd *cmd_list);
void	cmd_add_back(t_cmd **cmd_list, t_cmd *cmd);
void	cmd_clean(t_cmd	**cmd_list);

void	process_single_quotes(t_shell *shell);
void	process_double_quotes(t_shell *shell);
void	remove_quotes(t_shell *shell);

#endif
