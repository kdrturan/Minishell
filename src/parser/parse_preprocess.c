/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/01 00:36:24 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <debug.h>

static t_token	*convert_dollar_after_heredoc(t_shell *shell, t_token *token)
{
	if (!token || token->type != DOLLAR)
		return (token);
	if (token->next && token->next->type == WORD)
	{
		token_insert(&shell->token_list, token->next,
			token_new(shell, WORD, gc_track(&shell->gc,
				ft_strjoin("$", token->next->text))));
		token_remove(&shell->token_list, token->next);
	}
	token_remove(&shell->token_list, token);
	return (NULL);
}

static void	mark_here_dollars(t_shell *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			token = token->next;
			while (token && token->type != DOLLAR)
			{
				if (token->type == WORD)
					return ;
				token = token->next;
			}
			token = convert_dollar_after_heredoc(shell, token);
			continue ;
		}
		if (token)
			token = token->next;
	}
}

static void process_dollars(t_shell *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == DOLLAR)
			handle_dollar(shell, token);
		token = token->next;
	}
}

void	parse_preprocess(t_shell *shell)
{
	mark_here_dollars(shell);
	process_double_quotes(shell);
	process_quotes(shell);
	process_dollars(shell);
	merge_words_br(shell);
	remove_quotes(shell);
	merge_words_ar(shell);
}
