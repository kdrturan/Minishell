/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:32:27 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <token.h>
#include <minishell.h>
#include <libft.h>

t_token_type	token_seperator(char *value, int i)
{
	if(!value)
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
#include"debug.h"

void	parse(t_shell *shell)
{
	t_token_type	type;
	t_token			*list;
	int				i;

	list = NULL;
	i = 0;
	while (shell->cmd[i])
	{
		type = token_seperator(shell->cmd, i);
		if (type == WORD)
			add_word_token(shell->cmd, &i, &list);
		else if (type == HEREDOC || type == APPEND)
		{
			token_add_back(&list, token_new(type, ft_substr(shell->cmd, i, 2)));
			i += 2;
		}
		else
			token_add_back(&list, token_new(type, ft_substr(shell->cmd, i++, 1)));
	}
	token_parser(shell ,&list);
	debug_print_token_list(list);
	//token_clear(&list);
}
