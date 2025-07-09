/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:44:18 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 04:04:11 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <lexer.h>
#include <readline/readline.h>
#include <exec.h>
#include <signal_handler.h>

t_token	*will_complete(t_token *token)
{
	while (token && token->next)
		token = token->next;
	while (token && token->type == WS)
		token = token->prev;
	if (token && token->type == PIPE)
		return (token);
	return (NULL);
}

static int	append_pipe_input(t_shell *shell)
{
	char	*input;
	char	*trimmed;

	while (1)
	{
		input = gc_track(&shell->gc, readline(">"));
		if (!input)
		{
			print_error(false, NULL, NULL, E_SYNTAX);
			shell->exit_status = 2;
			ft_exit(shell, NULL);
		}
		trimmed = gc_track(&shell->gc, ft_strtrim(input, WHITESPACES));
		if (trimmed && trimmed[0] != '\0')
		{
			shell->input = gc_track(&shell->gc,
					ft_strjoin(shell->input, trimmed));
			lexer_run(shell);
			return (1);
		}
	}
	return (0);
}

void	complete_pipe(t_shell *shell)
{
	t_token	*token;

	token = will_complete(shell->token_list);
	if (token)
		append_pipe_input(shell);
}
