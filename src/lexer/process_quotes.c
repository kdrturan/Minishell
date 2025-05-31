/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:41:01 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 20:12:21 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	process_quote_token(t_shell *shell, t_token **token)
{
	char			*value;
	t_token			*new_token;
	t_token			*temp;
	t_token_type	type;

	type = (*token)->type;
	temp = *token;
	new_token = token_new(shell, WORD, NULL);
	new_token->type = WORD;
	new_token->prev = temp;
	temp = temp->next;
	value = NULL;
	while (temp && temp->type != type)
	{
		value = gc_track(&shell->gc, ft_strjoin(value, temp->text));
		temp->text = NULL;
		temp = temp->next;
		token_remove(&shell->token_list, temp->prev);
	}
	(*token)->next = new_token;
	new_token->next = temp;
	new_token->text = value;
	if (temp)
		temp->prev = new_token;
	*token = temp;
}
