/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:46:08 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 03:52:57 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	print_error(bool b_flag, char *sec0, char *sec1, const char *error)
{
	if (b_flag)
		ft_putstr_fd("OIIA OIIA: ", STDERR_FILENO);
	ft_putstr_fd(sec0, STDERR_FILENO);
	if (sec1)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(sec1, STDERR_FILENO);
	ft_putstr_fd((char *)error, STDERR_FILENO);
}
