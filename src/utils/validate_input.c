/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:25:22 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/04 17:27:00 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

bool	validate_input(char *input)
{
	size_t	i;
	size_t	quote_count;

	if (!input)
		return (false);
	i = 0;
	quote_count = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			;//quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		return (false);
	return (true);
}
