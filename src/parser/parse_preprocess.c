/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/04 16:32:31 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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
					return;
				token = token->next;
			}
			if (token && token->type == DOLLAR)
			{
				if (token->next && token->next->type == WORD)
				{
					token_insert(&shell->token_list, token->next,
						token_new(shell, WORD, gc_track(&shell->gc, ft_strjoin("$", token->next->text))));
					token_remove(&shell->token_list, token->next);
				}
				token_remove(&shell->token_list, token);
			}
			else
				break;
		}
		token = token->next;
	}
}

static void	remove_quotes(t_shell *shell)
{
	t_token	*token;
	t_token	*remove;

	if (!shell || !shell->token_list)
		return ;
	token = shell->token_list;
	while (token)
	{
		if (token->type == QUOTE || token->type == DQUOTE)
		{
			remove = token;
			token = token->next;
			token_remove(&shell->token_list, remove);
			continue ;
		}
		token = token->next;
	}
}

void	parse_preprocess(t_shell *shell)
{
	t_token	*token;

	token = shell->token_list;
	mark_here_dollars(shell);
	while (token)
	{
		if (token->type == DOLLAR)
			handle_dollar(shell, token);
		token = token->next;
	}
	merge_words_br(shell);
	remove_quotes(shell);
	merge_words_ar(shell);
}
