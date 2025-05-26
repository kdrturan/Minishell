/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:39:33 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/26 21:30:34 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static t_token	*token_last(t_token *token_list)
{
	t_token	*l_ptr;

	if (!token_list)
		return (NULL);
	l_ptr = token_list;
	while (l_ptr->next != NULL)
		l_ptr = l_ptr->next;
	return (l_ptr);
}

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
