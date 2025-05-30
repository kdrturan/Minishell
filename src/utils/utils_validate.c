/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:16:17 by kdrturan          #+#    #+#             */
/*   Updated: 2025/05/30 17:30:26 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

bool	is_valid_export_name(char *value, int i, int j)
{
	if (!value)
		return (false);
	if (!(i - j) && ft_isdigit(value[i]))
		return (false);
	if (ft_isalnum(value[i]) || value[i] == '_') 
		return (true);
	return (false);
}