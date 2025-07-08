/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:46:08 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/08 21:02:01 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void print_error(bool b_flag, char *sec0, char *sec1, char *error)
{
    if (b_flag)
        ft_putstr_fd("OIIA OIIA: ",2);
	ft_putstr_fd(sec0,2);
    if (sec1)
        ft_putstr_fd(": ",2);
	ft_putstr_fd(sec1 ,2);
	ft_putstr_fd(error,2);
}
