/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:07:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 17:30:18 by kdrturan         ###   ########.fr       */
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


bool	is_valid_export_name(char *value, int i, int j);


#endif