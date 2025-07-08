/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 05:30:19 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 01:41:14 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <token.h>

void	check_pipes(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->args == NULL || cmd->args[0] == NULL)
		{
			shell->exit_status = 2;
			return ;
		}
		cmd = cmd->next;
	}
}

void	check_redirs(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = shell->cmd_list;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->target == NULL)
			{
				shell->exit_status = 2;
				return ;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	check_quotes(t_shell *shell)
{
	t_token	*token;
	bool	in_squote;
	bool	in_dquote;

	in_squote = false;
	in_dquote = false;
	token = shell->token_list;
	while (token)
	{
		if (token->type == QUOTE && !in_dquote)
			in_squote = !in_squote;
		else if (token->type == DQUOTE && !in_squote)
			in_dquote = !in_dquote;
		token = token->next;
	}
	if (in_squote || in_dquote)
		shell->exit_status = 2;
}
