/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:50:57 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/25 17:47:12 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]) + 1))
		return (1);
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]) + 1))
		return (1);
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]) + 1))
		return (1);
	if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]) + 1))
		return (1);
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]) + 1))
		return (1);
	return (0);
}