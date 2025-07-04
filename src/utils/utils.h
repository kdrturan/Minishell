/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:07:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/04 19:49:25 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <token.h>
# include <libft.h>
# include <env.h>

int		is_white_space(
			int c);

char	*str_change(
			char *dst,
			char *src,
			size_t idx,
			size_t len);

int		get_valid_key_length(
			t_token *dollar);

bool	will_eat(
			char c);

bool	validate_input(
			t_shell *shell,
			char *input);

t_token	*skip_ws(
			t_token *tok);

char	*get_prompt(
			int status);

bool	ft_isnumeric(const char *str);

#endif