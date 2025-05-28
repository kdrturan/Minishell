/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:04:55 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 18:23:14 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include <minishell.h>
# include <token.h>
# include <libft.h>

void	parse(t_shell *shell);
int		is_white_space(int c);
void    token_parser(t_shell *shell,t_token **list);
t_token_type	token_seperator(char *value, int i);

#endif