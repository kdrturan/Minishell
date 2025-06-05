#ifndef TEST_H
# define TEST_H

# include <check.h>
# include <stdlib.h>
# include <parser.h>
# include <lexer.h>
# include <token.h>
# include <gc.h>
# include <init.h>
# include <env.h>
# include <minishell.h>
# include <libft.h>

extern char **g_envp; 

Suite *parser_core_suite(void);

#endif
