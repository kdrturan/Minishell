#include <check.h>
#include <stdlib.h>
#include <parser.h>
#include <lexer.h>
#include <token.h>
#include <gc.h>
#include <init.h>
#include <env.h>
#include <minishell.h>
#include <libft.h>

char **g_envp = NULL;

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

Suite *parser_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Parser");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_simple_echo_args);
	tcase_add_test(tc_core, test_ls_with_flag);
	tcase_add_test(tc_core, test_cat_multiple_files);
	suite_add_tcase(s, tc_core);

	return s;
}

int	main(int argc, char **argv, char **envp)
{
	int		number_failed;
	Suite	*s;
	SRunner	*sr;

	g_envp = envp;

	s = parser_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}