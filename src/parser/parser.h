/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:04:55 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/27 20:45:35 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
#include <token.h>

void	parse(char *input);
int		is_white_space(int c);
void    token_parser(t_token **list);


#endif