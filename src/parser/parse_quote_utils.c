/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 02:35:44 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/15 18:41:17 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	remove_quotes(t_shell *shell)
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

bool	will_expand(t_token	*f_token, t_token	*b_token)
{
	bool			flag;
	t_token_type	type;

	flag = false;
	while (b_token)
	{
		if (b_token->type == QUOTE || b_token->type == DQUOTE)
		{	flag = false;
			type = b_token->type;
			while(f_token)
			{
				if (f_token->type == type)
					flag = true;
				f_token = f_token->next;
			}
		}
		b_token = b_token->prev;
	}
	return (flag);
}

void	process_double_quotes(t_shell *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == DQUOTE && token->next)
		{
			token = token->next;
			while (token && token->type != DQUOTE)
			{
				if (token->type == DOLLAR)
				{
					if (will_expand(token, token))
						handle_dollar(shell, token);
				}
				token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}

static	t_token	*join_quote_block(
		t_shell *shell, t_token *token, t_token_type type)
{
	t_token	*tmp;

	token->text = gc_track(&shell->gc, ft_strdup(""));
	token->type = WORD;
	token = token->next;
	if (!token)
		return (NULL);
	while (token && token->type != type)
	{
		tmp = token;
		token = token->next;
		tmp->prev->text = gc_track(&shell->gc,
				ft_strjoin(tmp->prev->text, tmp->text));
		token_remove(&shell->token_list, tmp);
	}
	if (token && token->type == type)
	{
		tmp = token;
		token = token->next;
		token_remove(&shell->token_list, tmp);
	}
	return (token);
}

void	process_quotes(t_shell *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == QUOTE || token->type == DQUOTE)
			token = join_quote_block(shell, token, token->type);
		else
			token = token->next;
	}
}
