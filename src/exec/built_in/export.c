/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:53:36 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/05 16:45:08 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static bool	is_valid_key(char *key)
{
	if (!key)
		return (false);
	if (ft_isdigit(*key))
		return (false);
	while (*key)
	{
		if (ft_isalnum(*key) || *key == '_')
			key++;
		else
			return (false);
	}
	return (true);
}

static bool error_msg(t_shell *shell, char *arg)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd("‘", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("’", STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	shell->exit_status = 1;
}

void	export(t_shell *shell, t_cmd *cmd)
{
	size_t	i;
	size_t	start;
	char	*eq;
	char	*key;
	char	*val;

	i = 1;
	start = i;
	while (cmd->args[i])
	{
		eq = ft_strchr(cmd->args[i], '=');
		if (eq == cmd->args[i] && ft_strlen(cmd->args[i]) == 1)
		{
			error_msg(shell, cmd->args[i]);
			i++;
			continue;
		}
		if (eq)
		{
			key = gc_track(&shell->env_gc, ft_substr(cmd->args[i], 0, eq - cmd->args[i]));
			if (!is_valid_key(key))
			{
				error_msg(shell, cmd->args[i]);
				i++;
				continue;
			}
			val = gc_track(&shell->env_gc, ft_strdup(eq + 1));
			env_set(shell, key, val);
		}
		else
		{
			if (is_valid_key(cmd->args[i]))
			{
				key = gc_track(&shell->env_gc, ft_strdup(cmd->args[i]));
				val = NULL;
				env_set(shell, key, val);
			}
			else
				error_msg(shell, cmd->args[i]);
		}
		i++;
	}
	if (start == i)
	{
		while (start < shell->env->count)
		{
			printf("declare -x %s", shell->env->pairs[start].key);
			if (shell->env->pairs[start].val)
				printf("=\"%s\"", shell->env->pairs[start].val);
			printf("\n");
			start++;
		}
	}
}
