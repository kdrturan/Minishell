#include "../test.h"

START_TEST(test_expand_user_unquoted)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo $USER");

    lexer_run(&shell);
    parser_run(&shell);

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[0], "echo");
    ck_assert_str_eq(shell.cmd_list->args[1], getenv("USER"));
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_user_double_quotes)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo \"$USER\"");

    lexer_run(&shell);
    parser_run(&shell);

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[1], getenv("USER"));
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_no_expand_single_quotes)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo '$USER'");

    lexer_run(&shell);
    parser_run(&shell);

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[1], "$USER");
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_concat)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo abc$USERxyz");

    lexer_run(&shell);
    parser_run(&shell);

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[1], "abc");
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_multiple)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo \"$USER $HOME\"");

    lexer_run(&shell);
    parser_run(&shell);

    char *expected = gc_track(&shell.gc, ft_strjoin(getenv("USER"), " "));
    expected = gc_track(&shell.gc, ft_strjoin(expected, getenv("HOME")));

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[1], expected);
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_unset_var)
{
    t_shell shell;

    unsetenv("TESTVAR");

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo $TESTVAR");

    lexer_run(&shell);
    parser_run(&shell);

    ck_assert_ptr_nonnull(shell.cmd_list);
    if (shell.cmd_list->args[1])
        ck_assert_str_eq(shell.cmd_list->args[1], "");
    else
        ck_assert_ptr_null(shell.cmd_list->args[1]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_pid)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.input = ft_strdup("echo $$");

    lexer_run(&shell);
    parser_run(&shell);

    char *expected = gc_track(&shell.gc, ft_itoa(getpid()));

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[1], expected);
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

START_TEST(test_expand_exit_status)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(shell));
    gc_init(&shell.gc);
    init_shell(&shell, g_envp);

    shell.exit_status = 42;
    shell.input = ft_strdup("echo $?");

    lexer_run(&shell);
    parser_run(&shell);

    char *expected = gc_track(&shell.gc, ft_itoa(42));

    ck_assert_ptr_nonnull(shell.cmd_list);
    ck_assert_str_eq(shell.cmd_list->args[1], expected);
    ck_assert_ptr_null(shell.cmd_list->args[2]);

    cmd_clean(&shell.cmd_list);
    token_clean(&shell.token_list);
    free(shell.input);
    gc_free_all(&shell.gc);
}
END_TEST

Suite *parser_expand_suite(void)
{
    Suite *s;
    TCase *tc_expand;

    s = suite_create("Parser_Expand");
    tc_expand = tcase_create("Expand");

    tcase_add_test(tc_expand, test_expand_user_unquoted);
    tcase_add_test(tc_expand, test_expand_user_double_quotes);
    tcase_add_test(tc_expand, test_no_expand_single_quotes);
    tcase_add_test(tc_expand, test_expand_concat);
    tcase_add_test(tc_expand, test_expand_multiple);
    tcase_add_test(tc_expand, test_expand_unset_var);
    tcase_add_test(tc_expand, test_expand_pid);
    tcase_add_test(tc_expand, test_expand_exit_status);

    suite_add_tcase(s, tc_expand);
    return s;
}