/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:04:55 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 20:11:28 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <utils.h>
# include <token.h>
# include <minishell.h>
# include <libft.h>
# include <debug.h>
# include <env.h>

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

void			lexer_run(
					t_shell *shell);

void			process_tokens(
					t_shell *shell);

t_token_type	identify_tokens(
					char *value,
					int i);

void			process_quote_token(
					t_shell *shell,
					t_token **token);

#endif