/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:58:19 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/26 22:28:29 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	token_remove(t_token **head, t_token *node)
{
	if (!head || !*head || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	token_del(node);
}
