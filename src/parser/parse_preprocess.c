/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:48:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 03:03:11 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parse_preprocess(t_shell *shell)
{
	t_token *token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == DOLLAR)
			handle_dollar(shell, token);
		token = token->next;
	}
}
