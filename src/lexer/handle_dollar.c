/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:04 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 00:57:05 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <lexer.h>
#include <libft.h>
#include <minishell.h>
#include <stdlib.h>
#include <token.h>
#include <utils.h>

void	handle_dollar_token(t_shell *shell, t_token **dollar)
{
	t_token	*curr;
	char	*result;

	if (!dollar || !*dollar)
		return ;
	curr = *dollar;
	result = gc_track(&shell->gc, ft_strdup(""));
	while (curr && (curr->type == DOLLAR || curr->type == WORD))
	{
		if (curr->type == DOLLAR)
		{
			if (curr->next && curr->next->type == DOLLAR)
			{
				char *pid = gc_track(&shell->gc, ft_itoa(getpid()));
				result = gc_track(&shell->gc, ft_strjoin(result, pid));
				curr = curr->next;
			}
			else if (curr->next && curr->next->type == WORD && *curr->next->text == '?')
            {
                t_token *next = curr->next;
                char *ret = gc_track(&shell->gc, ft_itoa(31)); //will be replaced
                if (ft_strlen(next->text) > 1)
                {
                    char *rest = gc_track(&shell->gc, ft_strdup(next->text + 1));
                    char *combined = gc_track(&shell->gc, ft_strjoin(ret, rest));
                    result = gc_track(&shell->gc, ft_strjoin(result, combined));
                }
                else
                {
                    result = gc_track(&shell->gc, ft_strjoin(result, ret));
                }
                curr = curr->next;
            }
            else if (curr->next && curr->next->type == WORD && ft_isdigit(*curr->next->text))
            {x
                t_token *next = curr->next;
                if (ft_strlen(next->text) > 1)
                {
                    char *rest = gc_track(&shell->gc, ft_strdup(next->text + 1));
                    result = gc_track(&shell->gc, ft_strjoin(result, rest));
                }
                curr = curr->next;
            }
			else
			{
				result = gc_track(&shell->gc, ft_strjoin(result, "$"));
			}
		}
		else if (curr->type == WORD)
		{
			result = gc_track(&shell->gc, ft_strjoin(result, curr->text));
		}
		curr = curr->next;
	}
	(*dollar)->type = WORD;
	(*dollar)->text = result;
	t_token *tmp = (*dollar)->next;
	while (tmp != curr)
	{
		t_token *next = tmp->next;
		token_remove(&shell->token_list, tmp);
		tmp = next;
	}
	(*dollar)->next = curr;
	if (curr)
		curr->prev = *dollar;
}


