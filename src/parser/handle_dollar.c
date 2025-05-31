/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:43:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 19:25:00 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <debug.h>

static void expand_special(t_shell *shell, t_token *dollar)
{
    if (dollar->next->type == DOLLAR)
        dollar->text = gc_track(&shell->gc, ft_itoa(getpid()));
    else if (*(dollar->next->text) == '?')
        dollar->text = gc_track(&shell->gc, ft_itoa(8888));
    else if (*(dollar->next->text) == '-')
        dollar->text = gc_track(&shell->gc, ft_strdup("himBHs"));
    else if (will_eat(*(dollar->next->text)))
        dollar->text = gc_track(&shell->gc,
                ft_substr(dollar->next->text, 1,
                    ft_strlen(dollar->next->text) - 1));
    token_remove(shell->token_list, dollar->next);
}



static void env_insert_token(t_shell *shell, t_token *dollar, char *key)
{
	char	*val;
	size_t	i = 0;
	t_token	*insert = NULL;

	val = env_get_value(shell, key);
	if (!val)
		return;
	while (val[i])
	{
		if (is_white_space(val[i]))
		{
			size_t start = i;
			while (val[i] && is_white_space(val[i]))
				i++;
			token_add_back(&insert,
				token_new(shell, WS,
					gc_track(&shell->gc, ft_substr(val, start, i - start))));
		}
		else
		{
			size_t start = i;
			while (val[i] && !is_white_space(val[i]))
				i++;
			token_add_back(&insert,
				token_new(shell, WORD,
					gc_track(&shell->gc, ft_substr(val, start, i - start))));
		}
	}
	printf("-----INSERT-----\n");
	debug_print_token_list(insert);
	token_remove(&shell->token_list, dollar);
	token_insert(&shell->token_list, dollar->prev, insert);
}



static void expand_word(t_shell *shell, t_token *dollar)
{
    int     len;
    char    *key;

    len = get_valid_key_length(dollar);
    if (len == (int)ft_strlen(dollar->next->text))
        env_insert_token(shell, dollar,dollar->next->text);
    else
    {
        key = gc_track(&shell->gc, ft_substr(dollar->next->text, 0, len));
        env_insert_token(shell, dollar, key);
        dollar->next->text = gc_track(&shell->gc,
                ft_substr(dollar->next->text, len,
                    ft_strlen(dollar->next->text) - len));
    }
    token_remove(shell->token_list, dollar->next);
}

void    handle_dollar(t_shell *shell, t_token *dollar)
{
    if (!dollar)
        return ;
    if (!dollar->next)
        return (dollar->type = WORD);
    if (dollar->next->type == DQUOTE || dollar->next->type == QUOTE)
        token_remove(&shell->token_list, dollar);
    else if (dollar->next->type == DOLLAR
        || *(dollar->next->text) == '?'
        || *(dollar->next->text) == '-'
        || will_eat(*(dollar->next->text)))
        expand_special(shell, dollar);
    else if (dollar->next->type == WORD)
        expand_word(shell, dollar);
    dollar->type = WORD;
}
