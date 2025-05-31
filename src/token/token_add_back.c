/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:39:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 18:38:24 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

void	token_add_back(t_token **token_list, t_token *token)
{
	t_token	*last;

	if (!token_list || !(*token_list))
	{
		*token_list = token;
		return ;
	}
	last = token_last(*token_list);
	last->next = token;
	token->prev = last;
}
