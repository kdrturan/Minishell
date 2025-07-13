/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_interrupted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:44:04 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/14 02:25:18 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

bool	is_interrupted(int code)
{
	static bool	is_int;

	if (code == -1)
		return (is_int);
	is_int = !is_int;
	return (is_int);
}
