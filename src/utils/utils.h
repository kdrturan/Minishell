/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:07:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 00:31:06 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
#include <stdbool.h>
#include <libft.h>

int		is_white_space(
			int c);

char	*str_change(
			char *dst,
			char *src,
			size_t idx,
			size_t len);


bool	is_valid_export_char(char c);
bool	is_special_param(char c);


#endif