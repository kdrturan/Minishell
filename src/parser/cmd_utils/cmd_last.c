/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:52:58 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 17:54:52 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*cmd_last(t_cmd *cmd_list)
{
	t_cmd *l_ptr;

	if (!cmd_list)
		return (NULL);
	l_ptr = cmd_list;
	while (l_ptr->next != NULL)
		l_ptr = l_ptr->next;
	return (l_ptr);
}
