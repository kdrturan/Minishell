#include "../test.h"

static void run_validation_test(char *input, bool expect_fail)
{
	t_shell	shell;
	bool	result;

	ft_bzero(&shell, sizeof(shell));
	gc_init(&shell.gc);
	init_shell(&shell, g_envp);

	shell.input = ft_strdup(input);
	result = validate_input(&shell, shell.input);

	if (expect_fail)
	{
		ck_assert_msg(result == false, "Expected failure but got success on input: [%s]", input);
		ck_assert_int_eq(shell.exit_status, 258);
	}
	else
	{
		ck_assert_msg(result == true, "Expected success but got failure on input: [%s]", input);
	}

	free(shell.input);
	gc_free_all(&shell.gc);
}

START_TEST(test_pipe_start)
{
	run_validation_test("| ls", true);
}
END_TEST

START_TEST(test_pipe_end)
{
	run_validation_test("ls |", true);
}
END_TEST

START_TEST(test_valid_pipe)
{
	run_validation_test("ls | wc", false);
}
END_TEST

START_TEST(test_redir_no_target)
{
	run_validation_test("cat <", true);
}
END_TEST

START_TEST(test_redir_invalid_token)
{
	run_validation_test("ls < |", true);
}
END_TEST

START_TEST(test_redir_valid)
{
	run_validation_test("cat < infile", false);
}
END_TEST

START_TEST(test_redir_empty_expansion)
{
	unsetenv("EMPTY");
	run_validation_test("ls <$EMPTY", true);
}
END_TEST

START_TEST(test_redir_nonempty_expansion)
{
	setenv("FILE", "abc.txt", 1);
	run_validation_test("ls <$FILE", true);
}
END_TEST

Suite *validate_input_suite(void)
{
	Suite *s;
	TCase *tc;

	s = suite_create("Validate_Input");
	tc = tcase_create("Syntax_Validation");

	tcase_add_test(tc, test_pipe_start);
	tcase_add_test(tc, test_pipe_end);
	tcase_add_test(tc, test_valid_pipe);

	tcase_add_test(tc, test_redir_no_target);
	tcase_add_test(tc, test_redir_invalid_token);
	tcase_add_test(tc, test_redir_valid);

	tcase_add_test(tc, test_redir_empty_expansion);
	tcase_add_test(tc, test_redir_nonempty_expansion);

	suite_add_tcase(s, tc);
	return s;
}
