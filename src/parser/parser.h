/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:04:55 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:15:07 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

void			parse(
					t_shell *shell);

void			token_parser(
					t_shell *shell);

t_token_type	token_seperator(
					char *value,
					int i);

#endif