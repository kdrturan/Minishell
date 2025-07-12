/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:16:45 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/12 17:27:27 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	exit_code(int code)
{
	static int exit_code;

	if (code == -1)
		return (exit_code);
	exit_code = code;
	return (exit_code);
}