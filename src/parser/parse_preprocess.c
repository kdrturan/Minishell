/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 01:42:58 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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
