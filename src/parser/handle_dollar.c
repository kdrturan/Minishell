/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:43:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 16:56:57 by kdrturan         ###   ########.fr       */
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



static  void env_insert_token(t_shell *shell, t_token *dollar, char* key)
{
    t_token* new;
    size_t i;
    size_t j;
    size_t k;
    char *flag;

    k = 0;
    flag = NULL;
    j = 0;
    i = 0;
    dollar->text = env_get_value(shell, key);
    if (!dollar->text)
        return;
    while (dollar->text[i])
    {
        if (is_white_space(dollar->text[i]))
        {
            new = token_new(shell, WS, ft_strdup(" "));
            i++;
            j = i;
            while (dollar->text[i] && !is_white_space(dollar->text[i]))
                i++;
             new =token_new(shell, WORD, ft_substr(dollar->text, j, (i - j)));
        }
        if (!dollar->text[i])
        {
            return;
        }
        i++;
    }
    
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
