/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:11:11 by abturan           #+#    #+#             */
/*   Updated: 2025/07/12 23:11:21 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	exit_code(int code)
{
	static int	exit_code;

	if (code == -1)
		return (exit_code);
	exit_code = code;
	return (exit_code);
}
