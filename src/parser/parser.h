/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:21:19 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 14:14:31 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell.h>
# include <token.h>
# include <libft.h>
# include <unistd.h>
# include <utils.h>
# include <env.h>

void	parser_run(t_shell *shell);
void	parse_preprocess(t_shell *shell);
void	handle_dollar(t_shell *shell, t_token *dollar);

#endif
