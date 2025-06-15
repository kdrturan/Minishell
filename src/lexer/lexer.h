/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:04:55 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/11 19:54:57 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <debug.h>
# include <env.h>
# include <libft.h>
# include <minishell.h>
# include <token.h>
# include <utils.h>

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

void						lexer_run(t_shell *shell);
t_token_type				identify_tokens(char *value, int i);
void						process_quote_token(t_shell *shell,
								t_token **token);

#endif