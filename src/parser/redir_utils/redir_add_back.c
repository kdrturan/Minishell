/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:51:04 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 17:55:27 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	redir_add_back(t_redir **redir_list, t_redir *redir)
{
	t_redir	*last;

	if (!redir_list || !(*redir_list))
	{
		*redir_list = redir;
		return ;
	}
	last = redir_last(*redir_list);
	last->next = redir;
}
