/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:58:19 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 15:34:19 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdio.h>
void	token_remove(t_token **head, t_token *node)
{
	if (!head || !*head || !node)
	return ;
	if ((*head) == node)

		*head = ((*head)->next);
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
}
