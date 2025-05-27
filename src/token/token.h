/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:10 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 01:59:28 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

enum						e_token_type
{
	WORD,
	PIPE,
	HEREDOC,
	APPEND,
	QUOTE,
	DQUOTE,
	DOLLAR,
	INPUT,
	OUTPUT,
	WS,
	NONE
};

struct						s_token
{
	char					*text;

	t_token					*next;
	t_token					*prev;
	t_token_type			type;
};

t_token						*token_new(t_token_type type, char *text);
void						token_del(t_token *token);
void						token_clear(t_token **token_list);
void						token_remove(t_token **token_list, t_token *token);
void						token_add_back(t_token **token_list,
								t_token *token);

#endif