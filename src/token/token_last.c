/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:43 by kdrturan          #+#    #+#             */
/*   Updated: 2025/05/31 18:26:12 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

t_token	*token_last(t_token *token_list)
{
	t_token	*l_ptr;

	if (!token_list)
		return (NULL);
	l_ptr = token_list;
	while (l_ptr->next != NULL)
		l_ptr = l_ptr->next;
	return (l_ptr);
}
