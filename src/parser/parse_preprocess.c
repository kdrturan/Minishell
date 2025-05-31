/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 19:18:31 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	join_words(t_shell *shell)
{
	char *value;
	t_token	*token;
	
	token = shell->token_list;
	while (token)
	{
		if (token->type == DQUOTE)
		{
			token = token->next;
			if (!token->next)
				return;
				token->type = WORD;
			while (token &&  token->next  && token->next->type != DQUOTE)
			{
				value = gc_track(&shell->gc ,ft_strjoin(token->text, token->next->text));
				token->text = value;
				token_remove(&shell->token_list ,token->next);
			}
			token = token->next->next;
			continue;
		}
		if (token->next && token->type == WORD && token->next->type == WORD)
		{
			value = gc_track(&shell->gc ,ft_strjoin(token->text, token->next->text));
			token->text = value;
			token_remove(shell->token_list ,token->next);
		}
		token = token->next;	
	}
}

	

void	parse_preprocess(t_shell *shell)
{
	t_token *token;
	char *value;

	token = shell->token_list;
	while (token)
	{
		if (token->type == DOLLAR)
			handle_dollar(shell, token);
		token = token->next;
	}
	join_words(shell);
}
