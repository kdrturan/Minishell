#include "test.h"

char **g_envp = NULL;

int main(int argc, char **argv, char **envp)
{
    int     number_failed;
    SRunner *sr;

    g_envp = envp;

    sr = srunner_create(parser_core_suite());
    srunner_add_suite(sr, parser_quote_suite());
    srunner_add_suite(sr, parser_expand_suite());
    srunner_add_suite(sr, parser_redir_suite());
    srunner_add_suite(sr, parser_pipe_suite());
    srunner_add_suite(sr, parser_mix_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}