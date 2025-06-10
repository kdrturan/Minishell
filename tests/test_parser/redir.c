#include "../test.h"

START_TEST(test_single_output_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo hello > out.txt");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "hello");
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "out.txt");
	ck_assert_ptr_null(shell.cmd_list->redir->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_append_output_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo hello >> log.txt");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, APPEND);
	ck_assert_str_eq(shell.cmd_list->redir->target, "log.txt");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_input_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cat < in.txt");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, INPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "in.txt");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_multiple_output_redirs)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cmd arg1 > file1 > file2");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "file1");
	ck_assert_ptr_nonnull(shell.cmd_list->redir->next);
	ck_assert_int_eq(shell.cmd_list->redir->next->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->next->target, "file2");
	ck_assert_ptr_null(shell.cmd_list->redir->next->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_mixed_in_out_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cmd < in.txt > out.txt");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, INPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "in.txt");
	ck_assert_ptr_nonnull(shell.cmd_list->redir->next);
	ck_assert_int_eq(shell.cmd_list->redir->next->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->next->target, "out.txt");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_output_redir_no_space)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo hi>out");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "echo");
	ck_assert_str_eq(shell.cmd_list->args[1], "hi");
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "out");
	ck_assert_ptr_null(shell.cmd_list->redir->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_quoted_target_output_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo hi > \"out file.txt\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "out file.txt");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_heredoc_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cat << EOF");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, HEREDOC);
	ck_assert_str_eq(shell.cmd_list->redir->target, "EOF");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_duplicate_input_redir)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cmd < in1 < in2");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, INPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "in1");
	ck_assert_ptr_nonnull(shell.cmd_list->redir->next);
	ck_assert_int_eq(shell.cmd_list->redir->next->type, INPUT);
	ck_assert_str_eq(shell.cmd_list->redir->next->target, "in2");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_redir_before_command)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("> out.txt cmd arg");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_str_eq(shell.cmd_list->args[0], "cmd");
	ck_assert_str_eq(shell.cmd_list->args[1], "arg");
	ck_assert_int_eq(shell.cmd_list->redir->type, OUTPUT);
	ck_assert_str_eq(shell.cmd_list->redir->target, "out.txt");

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_heredoc_dollar_delim)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo << $USER");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, HEREDOC);
	ck_assert_str_eq(shell.cmd_list->redir->target, "$USER");
	ck_assert_ptr_null(shell.cmd_list->redir->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_heredoc_double_quoted_dollar)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo << \"$USER\"");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, HEREDOC);
	ck_assert_str_eq(shell.cmd_list->redir->target, "$USER");
	ck_assert_ptr_null(shell.cmd_list->redir->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_heredoc_single_quoted_dollar)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("echo << '$USER'");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, HEREDOC);
	ck_assert_str_eq(shell.cmd_list->redir->target, "$USER");
	ck_assert_ptr_null(shell.cmd_list->redir->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_heredoc_plain_delim)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup("cat << EOF");

	lexer_run(&shell);
	parser_run(&shell);

	ck_assert_ptr_nonnull(shell.cmd_list);
	ck_assert_int_eq(shell.cmd_list->redir->type, HEREDOC);
	ck_assert_str_eq(shell.cmd_list->redir->target, "EOF");
	ck_assert_ptr_null(shell.cmd_list->redir->next);

	cmd_clean(&shell.cmd_list);
	token_clean(&shell.token_list);
	free(shell.input);
	gc_free_all(&shell.gc);
}
END_TEST

Suite *parser_redir_suite(void)
{
	Suite *s;
	TCase *tc_redir;

	s = suite_create("Parser_Redir");
	tc_redir = tcase_create("Redirection");

	tcase_add_test(tc_redir, test_single_output_redir);
	tcase_add_test(tc_redir, test_append_output_redir);
	tcase_add_test(tc_redir, test_input_redir);
	tcase_add_test(tc_redir, test_multiple_output_redirs);
	tcase_add_test(tc_redir, test_mixed_in_out_redir);
	tcase_add_test(tc_redir, test_output_redir_no_space);
	tcase_add_test(tc_redir, test_quoted_target_output_redir);
	tcase_add_test(tc_redir, test_heredoc_redir);
	tcase_add_test(tc_redir, test_duplicate_input_redir);
	tcase_add_test(tc_redir, test_redir_before_command);
	tcase_add_test(tc_redir, test_heredoc_dollar_delim);
	tcase_add_test(tc_redir, test_heredoc_double_quoted_dollar);
	tcase_add_test(tc_redir, test_heredoc_single_quoted_dollar);
	tcase_add_test(tc_redir, test_heredoc_plain_delim);

	suite_add_tcase(s, tc_redir);
	return s;
}
