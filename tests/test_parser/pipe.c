#include "../test.h"

START_TEST(test_single_pipe)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("ls | wc");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "ls");
	ck_assert_ptr_nonnull(shell.cmd_list->next);
	ck_assert_str_eq(shell.cmd_list->next->args[0], "wc");
	ck_assert_ptr_null(shell.cmd_list->next->next);
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_pipe_no_spaces)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("ls|wc");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->args[0], "ls");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "wc");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_three_command_pipeline)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("echo a | grep a | wc -l");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "grep");
	ck_assert_str_eq(shell.cmd_list->next->next->args[0], "wc");
	ck_assert_ptr_null(shell.cmd_list->next->next->next);
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_pipe_with_input_redir_left)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("cat < in.txt | grep foo");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_int_eq(shell.cmd_list->redir->type, INPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "in.txt");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "grep");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_pipe_with_output_redir_right)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("grep foo file | sort > out.txt");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->next->args[0], "sort");
	ck_assert_int_eq(shell.cmd_list->next->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->next->redir->target, "out.txt");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_double_pipe_error)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("ls || wc");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "ls");
	ck_assert_ptr_null(shell.cmd_list->args[1]);
	ck_assert_ptr_nonnull(shell.cmd_list->next);
	ck_assert(!shell.cmd_list->next->args ||
	          !shell.cmd_list->next->args[0]);
	ck_assert_ptr_nonnull(shell.cmd_list->next->next);
	ck_assert_str_eq(shell.cmd_list->next->next->args[0], "wc");
	ck_assert_ptr_null(shell.cmd_list->next->next->args[1]);

	ck_assert_ptr_null(shell.cmd_list->next->next->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_quoted_pipe_literal)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("echo 'a|b' | cat");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->args[1], "a|b");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "cat");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_pipeline_with_tabs_spaces)
{
	t_shell shell;
	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);
	shell.input = ft_strdup("ls\t|\twc");
	lexer_run(&shell);
	parser_run(&shell);
	ck_assert_str_eq(shell.cmd_list->args[0], "ls");
	ck_assert_str_eq(shell.cmd_list->next->args[0], "wc");
	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

Suite *parser_pipe_suite(void)
{
	Suite *s;
	TCase *tc_pipe;

	s = suite_create("Parser_Pipe");
	tc_pipe = tcase_create("Pipe");

	tcase_add_test(tc_pipe, test_single_pipe);
	tcase_add_test(tc_pipe, test_pipe_no_spaces);
	tcase_add_test(tc_pipe, test_three_command_pipeline);
	tcase_add_test(tc_pipe, test_pipe_with_input_redir_left);
	tcase_add_test(tc_pipe, test_pipe_with_output_redir_right);
    tcase_add_test(tc_pipe, test_double_pipe_error);
	tcase_add_test(tc_pipe, test_quoted_pipe_literal);
	tcase_add_test(tc_pipe, test_pipeline_with_tabs_spaces);

	suite_add_tcase(s, tc_pipe);
	return s;
}