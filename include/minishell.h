/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:32:16 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <gc.h>

typedef struct s_shell      t_shell;
typedef struct s_env	    t_env;
typedef struct s_token		t_token;

struct  s_shell{
    char    *cmd;
    t_env   *env;
    t_token *token_list;
    t_gc    gc;
};

#endif