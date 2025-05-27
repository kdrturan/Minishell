/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:58 by abturan           #+#    #+#             */
/*   Updated: 2025/05/27 18:57:57 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void dquote_parser(t_token **list, t_token **token)
{
    char *value;
    t_token *new_token;

    new_token->type = WORD;
    new_token->prev = (*token)->prev;
    value = NULL;
    while ((*token)->type != DQUOTE)
    {
        value = ft_strjoin(value,(*token)->text);
        (*token)->text = NULL;
        token_remove(list,token);
        token = (*token)->next;
    }
    new_token->next = (*token);
    new_token->text = value;
}



void    token_parser(t_token **list)
{
    t_token *tmp;
    
    tmp = *list;
    while (tmp)
    {
        if (tmp->type == DQUOTE)
            dquote_parser(list,&tmp);
        
        tmp = tmp->next;
    }
    
    
}