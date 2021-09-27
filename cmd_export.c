#include "minishell.h"

char **cmd_export(char *cmd, char **envp)
{
    int i;
    char **path;

    path = ft_split2(cmd, ' ');
    if (!(ft_strcmp(cmd, "export")))
    {
        i = 0;
        while (envp[i])
        {
            printf("declare -x %s\n",envp[i]);
            i++;
        }
    }
    else
        envp = plus_line(envp, path[1]);
    return (envp);
}