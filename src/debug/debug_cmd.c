/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:58:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/01 18:01:35 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

static const char	*redir_type_to_str(t_redir_type type)
{
	if (type == R_OUT)
		return (">");
	if (type == R_OUT_APPEND)
		return (">>");
	if (type == R_IN)
		return ("<");
	if (type == R_HEREDOC)
		return ("<<");
	return ("?");
}

void	debug_print_redir(const t_redir *redir)
{
	while (redir)
	{
		printf("    [redir] %-3s -> \"%s\"\n",
			redir_type_to_str(redir->type),
			redir->target ? redir->target : "(null)");
		redir = redir->next;
	}
}

void	debug_print_cmd(const t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("─── command ───\n");
		printf("  argv :");
		if (!cmd->args || !cmd->args[0])
			printf(" (empty)");
		else
		{
			i = 0;
			while (cmd->args && cmd->args[i])
			{
				printf(" \"%s\"", cmd->args[i]);
				i++;
			}
		}
		printf("\n");
		if (cmd->redir)
			debug_print_redir(cmd->redir);
		else
			printf("    [redir] none\n");
		cmd = cmd->next;
	}
}
