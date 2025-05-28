/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:04:55 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 01:18:47 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSER_H
# define PARSER_H

#include <minishell.h>
#include <token.h>
typedef struct s_shell  t_shell;
void	parse(t_shell *shell);
int		is_white_space(int c);
void    token_parser(t_shell *shell,t_token **list);
t_token_type	token_seperator(char *value, int i);

#endif