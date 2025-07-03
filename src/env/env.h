/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:38:15 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/03 18:22:44 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <gc.h>
# include <libft.h>
# include <minishell.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_pair	t_pair;
typedef struct s_env	t_env;

struct					s_pair
{
	char				*key;
	char				*val;
};

struct					s_env
{
	t_pair				*pairs;
	size_t				count;
};

t_env					*env_parse(t_shell *shell, char **env_data);

void					env_set(t_shell *shell, char *key, char *val);

void					env_add(t_shell *shell, char *key, char *val);

t_env					*env_remove(t_shell *shell, char *key, t_gc *gc);

size_t					env_len(char **env, t_pair *pairs);

char					*env_get_value(t_shell *shell, char *key);

char					**env_cast_char(t_shell *shell);
void					cmd_run(t_shell *shell, t_cmd *cmd);
void					child_process(int prev_fd, t_shell *shell, t_cmd *cmd,
							int *pipe_fd);

#endif
