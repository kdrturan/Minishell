/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:22:48 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:35:46 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <minishell.h>

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
size_t					env_len(char **env, t_pair *pairs);
char					*env_get_value(t_shell *shell, char *key);

#endif
