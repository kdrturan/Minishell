/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:59:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 17:55:45 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	cmd_add_back(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*last;

	if (!cmd_list || !(*cmd_list))
	{
		*cmd_list = cmd;
		return ;
	}
	last = cmd_last(*cmd_list);
	last->next = cmd;
}
