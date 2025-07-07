/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:03:49 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/07 05:50:46 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static size_t	get_arg_count(t_token *token)
{
	size_t	n;

	n = 0;
	while (token && (token->type == WORD || token->type == WS))
	{
		if (token->type == WORD)
			n++;
		token = token->next;
	}
	return (n);
}

static char	**get_args(t_shell *shell)
{
	size_t	i;
	char	**args;

	i = 0;
	args = gc_track(&shell->gc,
			malloc(sizeof(char *) * (get_arg_count(shell->token_list) + 1)));
	while (shell->token_list && (shell->token_list->type == WORD
			|| shell->token_list->type == WS))
	{
		if (shell->token_list->type == WORD)
			args[i++] = shell->token_list->text;
		shell->token_list = shell->token_list->next;
	}
	args[i] = NULL;
	return (args);
}

static void	add_redir(t_shell *sh, t_token **tok,
						t_redir **lst, t_redir_type type)
{
	t_token	*op;
	t_token	*target;

	op = *tok;
	*tok = (*tok)->next;
	token_remove(&sh->token_list, op);
	*tok = skip_ws(*tok);
	if (!*tok || (*tok)->type == PIPE)
	{
		redir_add_back(lst, redir_new(sh, type, NULL));
		return ;
	}
	target = *tok;
	if (target->type != WORD)
	{
		redir_add_back(lst, redir_new(sh, type, NULL));
		return ;
	}
	redir_add_back(lst, redir_new(sh, type, target->text));
	*tok = target->next;
	token_remove(&sh->token_list, target);
	return ;
}

static t_redir	*get_redir(t_shell *shell, t_token *token)
{
	t_redir			*redir;
	t_redir_type	type;

	redir = NULL;
	while (token && (token->type != PIPE))
	{
		type = token->type;
		if (type == INPUT || type == OUTPUT
			|| type == HEREDOC || type == APPEND)
		{
			add_redir(shell, &token, &redir, type);
			continue ;
		}
		token = token->next;
	}
	return (redir);
}

void	generate_commands(t_shell *shell)
{
	t_redir	*redir;
	char	**args;

	args = NULL;
	redir = NULL;
	while (shell->token_list)
	{
		redir = get_redir(shell, shell->token_list);
		args = get_args(shell);
		cmd_add_back(&shell->cmd_list, cmd_new(shell, args, redir));
		if (shell->token_list && shell->token_list->type == PIPE
			&& shell->token_list->next == NULL)
		{
			cmd_add_back(&shell->cmd_list, cmd_new(shell, NULL, NULL));
			break ;
		}
		if (shell->token_list && shell->token_list->next)
			shell->token_list = shell->token_list->next;
		else
			break ;
	}
}
