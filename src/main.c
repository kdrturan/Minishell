#include "minishell.h"

int main()
{
    char *res = readline("Minishell");
    while (1)
    {
        add_history(res);
        printf("%s\n",res);
        free(res);
        res = readline("Minishell");
    }

    return (0);
}
