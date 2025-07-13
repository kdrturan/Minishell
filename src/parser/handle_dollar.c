/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:43:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/14 01:27:14 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	expand_special(t_shell *shell, t_token *dollar)
{
	if (dollar->next->type == DOLLAR)
		dollar->text = gc_track(&shell->gc, ft_itoa(ft_getpid()));
	else if (*(dollar->next->text) == '?')
	{
		dollar->text = gc_track(&shell->gc, ft_itoa(shell->exit_status));
		dollar->next->text = gc_track(&shell->gc,
				ft_strdup(dollar->next->text + 1));
		return ;
	}
	else if (*(dollar->next->text) == '-')
		dollar->text = gc_track(&shell->gc, ft_strdup("himBHs"));
	else if (will_eat(*(dollar->next->text)))
	{
		token_remove(&shell->token_list, dollar->next);
		token_remove(&shell->token_list, dollar);
		return ;
	}
	else
	{
		dollar->text = gc_track(&shell->gc,
				ft_substr(dollar->next->text, 1,
					ft_strlen(dollar->next->text) - 1));
	}
	token_remove(&shell->token_list, dollar->next);
}

static t_token	*tokenize_env_value(t_shell *s, char *val)
{
	t_token	*ins;
	size_t	i;
	size_t	start;

	ins = NULL;
	i = 0;
	while (val[i])
	{
		start = i;
		if (is_white_space(val[i]))
		{
			while (val[i] && is_white_space(val[i]))
				i++;
			token_add_back(&ins, token_new(s, WS,
					gc_track(&s->gc, ft_substr(val, start, i - start))));
		}
		else
		{
			while (val[i] && !is_white_space(val[i]))
				i++;
			token_add_back(&ins, token_new(s, WORD,
					gc_track(&s->gc, ft_substr(val, start, i - start))));
		}
	}
	return (ins);
}

void	env_insert_token(t_shell *shell, t_token *dollar, char *key)
{
	t_token	*insert;

	dollar->text = env_get_value(shell, key);
	if (!dollar->text)
		return ;
	dollar->text = dollar->text;
	insert = tokenize_env_value(shell, dollar->text);
	token_remove(&shell->token_list, dollar);
	token_insert(&shell->token_list, dollar->prev, insert);
}

static void	expand_word(t_shell *shell, t_token *dollar)
{
	size_t	len;
	char	*key;
	char	*rest;
	t_token	*orig_key;
	t_token	*rest_tok;

	len = get_valid_key_length(dollar);
	if (len == 0)
		return ;
	key = gc_track(&shell->gc, ft_substr(dollar->next->text, 0, len));
	orig_key = dollar->next;
	env_insert_token(shell, dollar, key);
	rest = orig_key->text + len;
	if (*rest)
	{
		rest_tok = token_new(shell, WORD,
				gc_track(&shell->gc, ft_strdup(rest)));
		token_insert(&shell->token_list, orig_key->prev, rest_tok);
	}
	token_remove(&shell->token_list, orig_key);
}

void	handle_dollar(t_shell *shell, t_token *dollar)
{
	if (!dollar)
		return ;
	if (!dollar->next)
	{
		dollar->type = WORD;
		return ;
	}
	if (dollar->next->type == DQUOTE || dollar->next->type == QUOTE)
	{
		dollar->type = WORD;
		dollar->text = gc_track(&shell->gc, ft_strdup("$"));
	}
	else if (dollar->next->type == DOLLAR
		|| *(dollar->next->text) == '?'
		|| *(dollar->next->text) == '-'
		|| will_eat(*(dollar->next->text)))
		expand_special(shell, dollar);
	else if (dollar->next->type == WORD)
		expand_word(shell, dollar);
	dollar->type = WORD;
}
