/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/14 01:43:41 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\001\033[1;32m\002🐱 OIIA $>\001\033[0m\002"
# define WHITESPACES " \t\n\v\f\r"

# include <gc.h>

typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;

struct	s_shell
{
	char					*input;
	char					*home_dir;
	t_env					*env;
	t_token					*token_list;
	t_cmd					*cmd_list;
	t_gc					gc;
	t_gc					env_gc;
	t_gc					exec_gc;
	int						exit_status;
	int						cmd_status;
};

#endif