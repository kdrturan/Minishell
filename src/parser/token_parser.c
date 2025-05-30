/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:15:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:17:40 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>
#include <token.h>
#include <minishell.h>
#include <libft.h>
#include <env.h>
#include <utils.h>

void	dollar_check(t_shell *shell, t_token *token)
{
	size_t	i;
	size_t	j;
	char	*expanse;
	char	*key;

	key = NULL;
	i = 0;
	j = 0;
	while (token->text[i])
	{
		if (token->text[i] == '$')
		{
			j = i;
			i++;
			while (token->text[i] != '\0' && token_seperator(token->text, i) == WORD)
			{
				key = gc_track(&shell->gc,ft_strjoin(key, gc_track(&shell->gc, ft_substr(token->text, i, 1))));
				i++;
			}
			expanse = env_get_value(shell, key);
			token->text = gc_track(&shell->gc, str_change(token->text,expanse,j,(i - j)));
			return (dollar_check(shell, token));
		}
		i++;
	}
}

void	dquote_parser(t_shell *shell, t_token **token)
{
	char	*value;
	t_token	*new_token;
	t_token	*temp;

	temp = *token;
	new_token = token_new(shell, WORD, NULL);
	new_token->type = WORD;
	new_token->prev = temp;
	temp = temp->next;
	value = NULL;
	while (temp->type != DQUOTE)
	{
		value = gc_track(&shell->gc, ft_strjoin(value,temp->text));
		temp->text = NULL;
		temp = temp->next;
		token_remove(&shell->token_list, temp->prev);
	}
	(*token)->next = new_token;
	temp->prev = new_token;
	*token = temp;
	new_token->next = temp;
	new_token->text = value;
	dollar_check(shell, new_token);
}

void	quote_parser(t_shell *shell, t_token **token)
{
	char	*value;
	t_token	*new_token;
	t_token	*temp;

	temp = *token;
	new_token = token_new(shell, WORD, NULL);
	new_token->type = WORD;
	new_token->prev = temp;
	temp = temp->next;
	value = NULL;
	while (temp->type != DQUOTE)
	{
		value = gc_track(&shell->gc, ft_strjoin(value,temp->text));
		temp->text = NULL;
		temp = temp->next;
		token_remove(&shell->token_list, temp->prev);
	}
	(*token)->next = new_token;
	temp->prev = new_token;
	*token = temp;
	new_token->next = temp;
	new_token->text = value;
}

void	token_parser(t_shell *shell)
{
	t_token *tmp;
	
	tmp = shell->token_list;
	while (tmp)
	{
		if (tmp->type == DQUOTE)
			dquote_parser(shell, &tmp);
		if (tmp->type == QUOTE)
			quote_parser(shell, &tmp);
		tmp = tmp->next;
	}
}
