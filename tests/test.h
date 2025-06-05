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
Suite *parser_quote_suite(void);
Suite *parser_expand_suite(void);
Suite *parser_redir_suite(void);
Suite *parser_pipe_suite(void);
Suite *parser_mix_suite(void);

#endif
