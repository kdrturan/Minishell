/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:44:18 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/08 21:18:29 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <lexer.h>
#include <readline/readline.h>

t_token	*will_complete(t_token *token)
{
	while (token->next)
		token = token->next;
	while (token && token->type == WS)
		token = token->prev;
	if (token && token->type == PIPE)
		return (token);
	return (NULL);
}

void	complete_pipe(t_shell *shell)
{
	t_token	*token;
	char	*input;

	token = will_complete(shell->token_list);
	if (token)
	{
		while (1)
		{
			input = gc_track(&shell->gc, ft_strtrim(gc_track(&shell->gc,
					readline(">")), WHITESPACES));
			if (input && input[0] != '\0')
			{
				shell->input = gc_track(&shell->gc, ft_strjoin(shell->input, input));
				lexer_run(shell);
				break;
			}
		}
		
	}
}
