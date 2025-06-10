#include "../test.h"

START_TEST(test_empty_input_should_fail)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_null(shell.cmd_list);

	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_single_argument_command)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("whoami");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "whoami");
	ck_assert_ptr_null(shell.cmd_list->args[1]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_multiple_spaces_between_args)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo     hello     world");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "hello");
	ck_assert_str_eq(shell.cmd_list->args[2], "world");
	ck_assert_ptr_null(shell.cmd_list->args[3]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_simple_echo_args)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo hello");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "hello");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_ls_with_flag)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("ls -la");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "ls");
	ck_assert_str_eq(shell.cmd_list->args[1], "-la");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_cat_multiple_files)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cat file1 file2 file3");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "cat");
	ck_assert_str_eq(shell.cmd_list->args[1], "file1");
	ck_assert_str_eq(shell.cmd_list->args[2], "file2");
	ck_assert_str_eq(shell.cmd_list->args[3], "file3");
	ck_assert_ptr_null(shell.cmd_list->args[4]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_tab_characters_between_args)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo\thello\t\tworld");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "hello");
	ck_assert_str_eq(shell.cmd_list->args[2], "world");
	ck_assert_ptr_null(shell.cmd_list->args[3]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_leading_trailing_spaces)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("   echo foo   ");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "foo");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_mixed_tabs_and_spaces)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo  \t \tbar");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "bar");
	ck_assert_ptr_null(shell.cmd_list->args[2]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_echo_with_trailing_spaces)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo      ");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	if (shell.cmd_list->args)
		ck_assert_ptr_null(shell.cmd_list->args[1]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_long_argument_list)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup(
		"cmd a1 a2 a3 a4 a5 a6 a7 a8 a9 a10");

	lexer_run(&shell);
	parser_run(&shell);

	const char *expect[] = {
		"cmd","a1","a2","a3","a4","a5","a6","a7","a8","a9","a10",NULL};
	for (int i = 0; expect[i]; ++i)
		ck_assert_str_eq(shell.cmd_list->args[i], expect[i]);
	ck_assert_ptr_null(shell.cmd_list->args[11]);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

Suite *parser_core_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Parser_Core");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_simple_echo_args);
	tcase_add_test(tc_core, test_ls_with_flag);
	tcase_add_test(tc_core, test_cat_multiple_files);
	tcase_add_test(tc_core, test_empty_input_should_fail);
	tcase_add_test(tc_core, test_single_argument_command);
	tcase_add_test(tc_core, test_multiple_spaces_between_args);
	tcase_add_test(tc_core, test_tab_characters_between_args);
	tcase_add_test(tc_core, test_leading_trailing_spaces);
	tcase_add_test(tc_core, test_mixed_tabs_and_spaces);
	tcase_add_test(tc_core, test_echo_with_trailing_spaces);
	tcase_add_test(tc_core, test_long_argument_list);
	suite_add_tcase(s, tc_core);

	return s;
}
