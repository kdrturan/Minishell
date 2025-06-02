/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:35:13 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/02 18:16:05 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*cmd_new(t_shell *shell, char **args, t_redir *redir)
{
	t_cmd	*cmd;

	if (!shell)
		return (NULL);
	cmd = gc_track(&shell->gc, malloc(sizeof(t_cmd)));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	if (args)
		cmd->args = args;
	cmd->redir = NULL;
	if (redir)
		cmd->redir = redir;
	cmd->next = NULL;
	return (cmd);
}
