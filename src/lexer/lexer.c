/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 21:11:47 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <token.h>
#include <minishell.h>
#include <libft.h>
#include <utils.h>
#include <debug.h>

static void	add_word_token(t_shell *shell, char *in, int *i)
{
	char	*val;
	int		start;

	start = *i;
	while (identify_tokens(in, *i) == WORD && in[*i])
		(*i)++;
	val = gc_track(&shell->gc, ft_substr(in, start, *i - start));
	token_add_back(&shell->token_list, token_new(shell, WORD, val));
}

void	lexer_run(t_shell *shell)
{
	t_token_type	type;
	int				i;

	i = 0;
	while (shell->cmd[i])
	{
		type = identify_tokens(shell->cmd, i);
		if (type == WORD)
			add_word_token(shell, shell->cmd, &i);
		else if (type == HEREDOC || type == APPEND)
		{
			token_add_back(&shell->token_list,
				token_new(shell, type,
					gc_track(&shell->gc, ft_substr(shell->cmd, i, 2))));
			i += 2;
		}
		else
			token_add_back(&shell->token_list,
				token_new(shell, type,
					gc_track(&shell->gc, ft_substr(shell->cmd, i++, 1))));
	}
	process_tokens(shell);
	debug_print_token_list(shell->token_list);
}
