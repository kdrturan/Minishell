/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_preprocess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:16:28 by abturan           #+#    #+#             */
/*   Updated: 2025/07/13 22:22:17 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <exec.h>
#include <stdio.h>
#include <sys/stat.h>

void	handle_error(t_cmd *cmd, int *status)
{
	struct stat	statbuf;

	if (cmd->args && cmd->args[0] && cmd->args[0][0] == '\0')
	{
		print_error(true, cmd->args[0], NULL, E_CMD0);
		*status = 127;
	}
	else if (errno == EACCES)
	{
		if (stat(cmd->args[0], &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
			print_error(true, cmd->args[0], NULL, E_FILE2);
		else
			print_error(true, cmd->args[0], NULL, E_PERM0);
		*status = 126;
	}
	else if (errno == ENOENT)
	{
		print_error(true, cmd->args[0], NULL, E_CMD0);
		*status = 127;
	}
	else
		*status = 1;
}

void	pre_check_part(struct stat st, char *cmd, int *status)
{
	if (S_ISDIR(st.st_mode))
	{
		print_error(true, cmd, NULL, E_FILE2);
		*status = 126;
	}
	else if (access(cmd, X_OK) == -1)
	{
		print_error(true, cmd, NULL, E_PERM0);
		*status = 126;
	}
}

void	pre_check(char *cmd, int *status)
{
	struct stat	st;

	if (cmd && ft_strchr(cmd, '/'))
	{
		if (cmd && stat(cmd, &st) == 0)
			pre_check_part(st, cmd, status);
		else
		{
			print_error(true, cmd, NULL, E_FILE0);
			*status = 127;
		}
	}
	else if (cmd && access(cmd, F_OK) == 0)
	{
		print_error(true, cmd, NULL, E_CMD0);
		*status = 127;
	}
	else
		*status = 0;
}
