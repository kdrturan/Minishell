/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:21:19 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 18:06:52 by tuaydin          ###   ########.fr       */
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

typedef enum e_redir_type
{
	R_OUT,
	R_OUT_APPEND,
	R_IN,
	R_HEREDOC 
}	t_redir_type;


typedef	struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;

struct	s_redir
{
	t_redir_type	type;
	char		*target;
	t_redir		*next;
};

struct	s_cmd
{
	char	**args;
	t_redir *redir;
	t_cmd	*next;
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
			
#endif
