/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:07:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/06 02:55:45 by tuaydin          ###   ########.fr       */
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

#endif