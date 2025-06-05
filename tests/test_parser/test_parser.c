#include "../test.h"

char **g_envp = NULL;

int	main(int argc, char **argv, char **envp)
{
	int		number_failed;
	Suite	*s;
	SRunner	*sr;

	g_envp = envp;

	s = parser_core_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}