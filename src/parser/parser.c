/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 15:45:54 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"
static	t_token_type	token_seperator(char *value, int i)
{
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

static void	add_word_token(char *in, int *i, t_token **lst)
{
	char	*val;
	int		start;

	start = *i;
	while (token_seperator(in, *i) == WORD && in[*i])
		(*i)++;
	val = ft_substr(in, start, *i - start);
	token_add_back(lst, token_new(WORD, val));
}

void	parse(char *input)
{
	t_token_type	type;
	t_token			*list;
	int				i;

	list = NULL;
	i = 0;
	while (input[i])
	{
		type = token_seperator(input, i);
		if (type == WORD)
			add_word_token(input, &i, &list);
		else if (type == HEREDOC || type == APPEND)
		{
			token_add_back(&list, token_new(type, ft_substr(input, i, 2)));
			i += 2;
		}
		else
			token_add_back(&list, token_new(type, ft_substr(input, i++, 1)));
	}
	token_clear(&list);
}
