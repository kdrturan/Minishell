/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:35:13 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/03 19:20:39 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*cmd_new(t_shell *shell, char **args, t_redir *redir)
{
	t_cmd	*cmd;

	cmd = gc_track(&shell->gc, malloc(sizeof(t_cmd)));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->args = args;
	cmd->redir = redir;
	cmd->next = NULL;
	cmd->status = 0;
	return (cmd);
}
