#include "minishell.h"

/*char *change_env(char *new_env)
{
    int i;
    char *new_str;
    int check;

    check = 0;
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(new_env) + 2));
    i = 0;
    while (new_env[i])
    {
        new_str[check] = new_env[i];
        check++;
        i++;
        if (new_env[i] == '=')
        {
            
            check += 1;
        }
    }

}*/

char **plus_line(char **env, char *new_env)
{
    char **envp;
   // char *new_change_env;
    int i;

    //new_change_env = change_env(new_env);
    i = 0;
    while(env[i])
        i++;
    envp = (char **)malloc(sizeof(char **) * (i + 1));
    i = 0;
    while (env[i])
    {
        envp[i] = env[i];
        i++;
    }
    envp[i] = new_env;
    return (envp);
}

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
    i = 0;
    while (envp[i])
        i++;
    return (envp);
}

int    print_export(char *str, char **envp)
{
    char *new_str;

    new_str = str + 1;
    printf("new_str = %s\n", new_str);
    printf("%s\n", envp[1]);
    return (1);
}