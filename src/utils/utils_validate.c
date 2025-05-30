/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:16:17 by kdrturan          #+#    #+#             */
/*   Updated: 2025/05/31 00:30:56 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

bool	is_valid_export_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_special_param(char c)
{
	return (c == '?' || c == '$');
}
