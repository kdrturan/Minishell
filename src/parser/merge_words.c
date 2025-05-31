/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:53:34 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 01:52:18 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	merge_quoted_words(t_shell *shell, t_token **token)
{
	char	*value;

	*token = (*token)->next;
	if (!(*token) || !(*token)->next)
		return ;
	if ((*token)->type == DQUOTE)
	{
		(*token)->type = WORD;
		(*token)->text = gc_track(&shell->gc, ft_strdup(""));
		if ((*token)->next && (*token)->next->type == DQUOTE)
			token_remove(&shell->token_list, (*token)->next);
		*token = (*token)->next;
		return ;
	}
	(*token)->type = WORD;
	while ((*token) && (*token)->next
		&& (*token)->next->type != DQUOTE)
	{
		value = gc_track(&shell->gc, ft_strjoin((*token)->text,
					(*token)->next->text));
		(*token)->text = value;
		token_remove(&shell->token_list, (*token)->next);
	}
	if (*token && (*token)->next)
		*token = (*token)->next->next;
}

void	merge_words_br(t_shell *shell)
{
	char	*value;
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == DQUOTE)
		{
			merge_quoted_words(shell, &token);
			continue ;
		}
		if (token->next && token->type == WORD
			&& token->next->type == WORD)
		{
			value = gc_track(&shell->gc, ft_strjoin(token->text,
						token->next->text));
			token->text = value;
			token_remove(&shell->token_list, token->next);
		}
		token = token->next;
	}
}

void	merge_words_ar(t_shell *shell)
{
	t_token	*token;
	char	*value;

	token = shell->token_list;
	while (token && token->next)
	{
		if (token->type == WORD && token->next->type == WORD)
		{
			value = gc_track(&shell->gc,
					ft_strjoin(token->text, token->next->text));
			token->text = value;
			token_remove(&shell->token_list, token->next);
			continue ;
		}
		token = token->next;
	}
}
