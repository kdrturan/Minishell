/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:42:21 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 20:07:17 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

void	token_insert(t_token **token_list, t_token *pos, t_token *new_list)
{
	t_token	*new_last;

	if (!token_list || !new_list)
		return ;
	new_last = token_last(new_list);
	if (!*token_list || !pos)
	{
		if (*token_list)
		{
			new_last->next = *token_list;
			(*token_list)->prev = new_last;
		}
		*token_list = new_list;
		new_list->prev = NULL;
		return ;
	}
	new_last->next = pos->next;
	if (pos->next)
		pos->next->prev = new_last;
	pos->next = new_list;
	new_list->prev = pos;
}
