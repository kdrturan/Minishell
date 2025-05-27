/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 01:16:03 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <token.h>
# include <parser.h>
# include <signal_handler.h>
# include <utils.h>
#include "../env/env.h"


# include <debug.h>

typedef struct s_shell  t_shell;

struct  s_shell{
    char    *cmd;
    t_env   *env;
};

#endif