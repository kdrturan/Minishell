/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:28:36 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/03 14:30:26 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

t_token	*skip_ws(t_token *tok)
{
	while (tok && tok->type == WS)
		tok = tok->next;
	return (tok);
}
