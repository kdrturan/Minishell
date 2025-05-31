/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:15:11 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 14:14:05 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

t_token	*token_new(t_shell *shell, t_token_type type, char *text)
{
	t_token	*token;

	token = gc_track(&shell->gc, malloc(sizeof(t_token)));
	if (!token)
		return (NULL);
	token->text = text;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
