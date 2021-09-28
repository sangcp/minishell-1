#include "minishell.h"

int find_equal(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int cmd_env(char *cmd, char **envp)
{
    char **path;
    int i;

    i = 0;
    path = ft_split2(cmd,' ');
    if (!(ft_strcmp(cmd,"env")))
    {
        while (envp[i])
        {
            printf("%s\n", envp[i]);
            i++;
        }
    }
    else
    {
        while (envp[i])
        {
            printf("%s\n", envp[i]);
            i++;
        }
        if (find_equal(path[1]))
            printf("%s\n",path[1]);
        else
            printf("env : %s: No such file or directory\n", path[1]);
    }
    return (1);
}