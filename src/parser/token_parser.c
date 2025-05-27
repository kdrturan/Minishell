/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:58 by abturan           #+#    #+#             */
/*   Updated: 2025/05/28 00:29:21 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void dquote_parser(t_token **list, t_token **token)
{
    char *value;
    t_token *new_token;
    t_token* temp = *token;

    new_token = token_new(WORD, NULL);
    new_token->type = WORD;
    new_token->prev = temp;
    temp = temp->next;
    value = NULL;
    while (temp->type != DQUOTE)
    {
        value = ft_strjoin(value,temp->text);
        temp->text = NULL;
        temp = temp->next;
        token_remove(list, temp->prev);
    }
    (*token)->next = new_token;
    temp->prev = new_token;
    *token = temp;
    new_token->next = temp;
    new_token->text = value;
}

void quote_parser(t_token **list, t_token **token)
{
    char *value;
    t_token *new_token;
    t_token* temp = *token;

    new_token = token_new(WORD, NULL);
    new_token->type = WORD;
    new_token->prev = temp;
    temp = temp->next;
    value = NULL;
    while (temp->type != DQUOTE)
    {
        value = ft_strjoin(value,temp->text);
        temp->text = NULL;
        temp = temp->next;
        token_remove(list, temp->prev);
    }
    (*token)->next = new_token;
    temp->prev = new_token;
    *token = temp;
    new_token->next = temp;
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
        if (tmp->type == QUOTE)
            quote_parser(list,&tmp);
        tmp = tmp->next;
    }
}