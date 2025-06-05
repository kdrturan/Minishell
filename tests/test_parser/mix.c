#include "../test.h"

START_TEST(test_pipe_redir_expand_doublequote)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("echo \"$USER\" | grep u > out.txt");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], getenv("USER"));
	ck_assert_str_eq(shell.cmd_list->next->args[0], "grep");
	ck_assert_str_eq(shell.cmd_list->next->args[1], "u");
	ck_assert_int_eq(shell.cmd_list->next->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->next->redir->target, "out.txt");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_input_pipe_append_output)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("cat < in.txt | sort >> log.txt");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_int_eq(shell.cmd_list->redir->type, INPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "in.txt");
	ck_assert_int_eq(shell.cmd_list->next->redir->type, APPEND);
	ck_assert_str_eq(shell.cmd_list->next->redir->target, "log.txt");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_multiple_pipes_with_quotes)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("echo 'a|b' | grep b | wc -l");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->args[1], "a|b");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "grep");
	ck_assert_str_eq(shell.cmd_list->next->next->args[0], "wc");
	ck_assert_str_eq(shell.cmd_list->next->next->args[1], "-l");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_heredoc_then_pipe)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("cat << EOF | wc");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_int_eq(shell.cmd_list->redir->type, HEREDOC);
	ck_assert_str_eq(shell.cmd_list->redir->target, "EOF");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "wc");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_redir_before_pipeline)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("> out.txt echo hello | cat");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "out.txt");
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "cat");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_in_quoted_redir_target)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("echo hi > \"$USER.txt\"");
	lexer_run(&shell);
	parser_run(&shell);
	char *exp = gc_track(&shell.gc, ft_strjoin(getenv("USER"), ".txt"));
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, exp);
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_mixed_single_double_quotes_and_expand)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("echo 'user:'\"$USER\"");
	lexer_run(&shell);
	parser_run(&shell);
	char *exp = gc_track(&shell.gc, ft_strjoin("user:", getenv("USER")));
	ck_assert_str_eq(shell.cmd_list->args[1], exp);
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

Suite *parser_mix_suite(void)
{
	Suite *s;
	TCase *tc_mix;
	s = suite_create("Parser_Mix");
	tc_mix = tcase_create("Mix");
	tcase_add_test(tc_mix, test_pipe_redir_expand_doublequote);
	tcase_add_test(tc_mix, test_input_pipe_append_output);
	tcase_add_test(tc_mix, test_multiple_pipes_with_quotes);
	tcase_add_test(tc_mix, test_heredoc_then_pipe);
	tcase_add_test(tc_mix, test_redir_before_pipeline);
	tcase_add_test(tc_mix, test_expand_in_quoted_redir_target);
	tcase_add_test(tc_mix, test_mixed_single_double_quotes_and_expand);
	suite_add_tcase(s, tc_mix);
	return s;
}