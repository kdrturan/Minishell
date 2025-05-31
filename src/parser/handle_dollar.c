/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:43:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 15:33:53 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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

static void expand_word(t_shell *shell, t_token *dollar)
{
    int     len;
    char    *key;

    len = get_valid_key_length(dollar);
    if (len == (int)ft_strlen(dollar->next->text))
        dollar->text = env_get_value(shell, dollar->next->text);
    else
    {
        key = gc_track(&shell->gc, ft_substr(dollar->next->text, 0, len));
        dollar->text = env_get_value(shell, key);
        dollar->next->text = gc_track(&shell->gc,
                ft_substr(dollar->next->text, len,
                    ft_strlen(dollar->next->text) - len));
    }
    token_remove(shell->token_list, dollar->next);
}

void    handle_dollar(t_shell *shell, t_token *dollar)
{
    if (!dollar || !dollar->next)
        return ;
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
