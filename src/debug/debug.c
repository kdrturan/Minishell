/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:10:01 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 05:17:59 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*token_type_to_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == QUOTE)
		return ("QUOTE");
	else if (type == DQUOTE)
		return ("DQUOTE");
	else if (type == DOLLAR)
		return ("DOLLAR");
	else if (type == INPUT)
		return ("INPUT");
	else if (type == OUTPUT)
		return ("OUTPUT");
	else if (type == WS)
		return ("WHITESPACE");
	return ("UNKNOWN");
}

void	print_token_list(t_token *list)
{
	const char	*text;

	while (list)
	{
		if (list->text)
			text = list->text;
		else
			text = "(null)";
		printf("Type: %-10s | Text: \"%s\"\n",
			token_type_to_str(list->type),
			text);
		list = list->next;
	}
}
