/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:57:56 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/06 19:15:49 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

static void	env_parse_line(t_shell *shell, t_pair *pair, char *line)
{
	char	*eq;
	size_t	len;

	eq = ft_strchr(line, '=');
	if (eq)
	{
		len = eq - line;
		pair->key = gc_track(&shell->env_gc, ft_substr(line, 0, len));
		pair->val = gc_track(&shell->env_gc, ft_strdup(eq + 1));
	}
	else
	{
		pair->key = gc_track(&shell->env_gc, ft_strdup(line));
		pair->val = NULL;
	}
}

t_env	*env_parse(t_shell *shell, char **env_data)
{
	t_env	*env;
	size_t	i;

	env = gc_track(&shell->env_gc, malloc(sizeof(t_env)));
	env->count = env_len(env_data, NULL);
	env->pairs = gc_track(&shell->env_gc,
			malloc(sizeof(t_pair) * env->count));
	i = 0;
	while (env_data[i])
	{
		env_parse_line(shell, &env->pairs[i], env_data[i]);
		i++;
	}
	return (env);
}
