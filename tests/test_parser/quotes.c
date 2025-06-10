#include "../test.h"

START_TEST(test_double_quotes_with_spaces)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo \"hello world\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "hello world");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_single_quotes_with_spaces)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo 'foo bar baz'");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "foo bar baz");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_empty_double_quotes)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo \"\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_ptr_null(shell.cmd_list->args[1]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_empty_single_quotes)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo ''");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_concat_unquoted_and_quoted)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo foo\"bar\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[1], "foobar");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_concat_two_double_quotes)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo \"foo\"\"bar\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[1], "foobar");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_concat_single_and_double_quotes)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo 'foo'\"bar\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[1], "foobar");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

Suite *parser_quote_suite(void)
{
    Suite *s;
    TCase *tc_quote;

    s = suite_create("Parser_Quote");
    tc_quote = tcase_create("Quote");

    tcase_add_test(tc_quote, test_double_quotes_with_spaces);
    tcase_add_test(tc_quote, test_single_quotes_with_spaces);
    tcase_add_test(tc_quote, test_empty_double_quotes);
    tcase_add_test(tc_quote, test_empty_single_quotes);
    tcase_add_test(tc_quote, test_concat_unquoted_and_quoted);
    tcase_add_test(tc_quote, test_concat_two_double_quotes);
    tcase_add_test(tc_quote, test_concat_single_and_double_quotes);

    suite_add_tcase(s, tc_quote);
    return s;
}
