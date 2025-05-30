/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:29:29 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:29:51 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

void	token_clean(t_token **token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		current->prev = NULL;
		current->text = NULL;
		current->type = NONE;
		current = next;
	}
	*token_list = NULL;
}
