/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:41:01 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 23:10:09 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <token.h>
#include <minishell.h>
#include <libft.h>
#include <env.h>
#include <utils.h>

void	dollar_check_in_dquote(t_shell *shell, t_token *token)
{
	size_t	i = 0;

    (void)shell;
	while (token->text && token->text[i])
	{
		break;
	}
}

void	process_dquote(t_shell *shell, t_token **token)
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
	dollar_check_in_dquote(shell, new_token);
}

void	process_quote(t_shell *shell, t_token **token)
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
	while (temp->type != QUOTE)
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
