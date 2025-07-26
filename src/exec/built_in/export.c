/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:53:36 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/26 14:13:55 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static void	print_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->env->count)
	{
		printf("declare -x %s", shell->env->pairs[i].key);
		if (shell->env->pairs[i].val)
			printf("=\"%s\"", shell->env->pairs[i].val);
		printf("\n");
		i++;
	}
}

static void	error_and_set(t_shell *shell, char *cmd_name, char *arg)
{
	print_error(true, cmd_name, arg, E_ARG2);
	shell->exit_status = 1;
}

static void	process_with_equal(
		t_shell *shell, char *cmd_name, char *arg, char *eq)
{
	char	*key;
	char	*val;

	key = gc_track(&shell->env_gc, ft_substr(arg, 0, eq - arg));
	if (!is_valid_key(key))
	{
		error_and_set(shell, cmd_name, arg);
		return ;
	}
	val = gc_track(&shell->env_gc, ft_strdup(eq + 1));
	env_set(shell, key, val);
}

static void	process_arg(t_shell *shell, char *cmd_name, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq == arg && ft_strlen(arg) == 1)
	{
		error_and_set(shell, cmd_name, arg);
		return ;
	}
	if (eq)
		process_with_equal(shell, cmd_name, arg, eq);
	else if (is_valid_key(arg))
	{
		key = gc_track(&shell->env_gc, ft_strdup(arg));
		env_set(shell, key, NULL);
	}
	else
		error_and_set(shell, cmd_name, arg);
}

void	export(t_shell *shell, t_cmd *cmd)
{
	size_t	i;

	shell->exit_status = 0;
	if (!cmd->args[1])
	{
		print_env(shell);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		process_arg(shell, cmd->args[0], cmd->args[i]);
		i++;
	}
}
