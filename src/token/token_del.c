/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:37:02 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/26 22:09:28 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	token_del(t_token *token)
{
	if (token)
	{
		free(token->text);
		free(token);
	}
}
