/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:51:23 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/26 22:29:30 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	token_clear(t_token **token_list)
{
	t_token	*temp;

	if (!token_list || !(*token_list))
		return ;
	while ((*token_list))
	{
		temp = (*token_list)->next;
		token_del((*token_list));
		(*token_list) = temp;
	}
}
