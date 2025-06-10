/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:38:15 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/10 16:38:18 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <minishell.h>
# include <libft.h>
# include <string.h>
# include <gc.h>

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

t_env					*env_parse(
							t_shell *shell,
							char **env_data);

void					env_set(
							t_shell *shell,
							char *key,
							char *val);

void					env_add(
							t_shell *shell,
							char *key,
							char *val);

void					env_remove(
							t_shell *shell,
							char *key);

size_t					env_len(
							char **env,
							t_pair *pairs);

char					*env_get_value(
							t_shell *shell,
							char *key);



char	**env_get_char(t_shell *shell);
void cmd_run(t_shell *shell, t_cmd *cmd);
void	child_process(int prev_fd, t_shell *shell, t_cmd *cmd, int *pipe_fd);


#endif
