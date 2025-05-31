/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:43:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 03:40:04 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <unistd.h>
#include <utils.h>
#include <libft.h>
#include <env.h>

void	handle_dollar(t_shell *shell, t_token *dollar)
{
	int	valid;
	
	valid = 0;
	if (dollar && dollar->next && dollar->next->text)
	{
		if (dollar->next->type == DOLLAR)
		{
			dollar->text = gc_track(&shell->gc, ft_itoa(getpid()));
			dollar->type = WORD;
			token_remove(shell->token_list, dollar->next);
		}
		else if (*dollar->next->text == '?')
		{
			dollar->text = gc_track(&shell->gc, ft_itoa(8888));
			dollar->type = WORD;
			token_remove(shell->token_list, dollar->next);
		}
		else if (ft_isdigit(*dollar->next->text))
		{
			dollar->next->text = gc_track(&shell->gc, ft_substr(dollar->next->text, 1, ft_strlen(dollar->next->text) - 1));
			token_remove(shell->token_list, dollar);
		}
		else if (dollar->next->type == WORD)
		{
			valid = get_valid_key_length(dollar);
			if (valid == ft_strlen(dollar->next->text))
			{
				dollar->text = env_get_value(shell, dollar->next->text);
				token_remove(shell->token_list, dollar->next);
			}
			else
			{
				dollar->text = env_get_value(shell, gc_track(&shell->gc, ft_substr(dollar->next->text, 0, valid)));
				dollar->next->text = gc_track(&shell->gc, ft_substr(dollar->next->text, valid, ft_strlen(dollar->next->text) - valid));	
			}
			dollar->type = WORD;
		}
	}
}
