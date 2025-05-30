/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_seperator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:14:14 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:25:32 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <utils.h>

t_token_type	token_seperator(char *value, int i)
{
	if (!value)
		return (NONE);
	if (value[i] == '\'')
		return (QUOTE);
	else if (value[i] == '\"')
		return (DQUOTE);
	else if (value[i] == '$')
		return (DOLLAR);
	else if (value[i] == '|')
		return (PIPE);
	else if (is_white_space(value[i]))
		return (WS);
	else if (value[i] == '<')
	{
		if (value[i + 1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (value[i] == '>')
	{
		if (value[i + 1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	return (WORD);
}
