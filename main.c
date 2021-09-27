#include "minishell.h"

void	ef_init(t_ef *ef)
{
	ef->row = 0;
	ef->i = 0;
}

void	plus_row(char *str, t_ef *ef, char c)
{
	ef->row++;
	while (str[ef->i] && str[ef->i] == c)
		ef->i++;
}

void	plus_i(char *str, t_ef *ef)
{
	while (str[ef->i] && (str[ef->i] != '\''
		|| str[ef->i] != '\\' || str[ef->i] != '\"'))
		ef->i++;
}

int	check_row(char *str, char c)
{
	t_ef	ef;

	ef_init(&ef);
	while (str[ef.i] && str[ef.i] == c)
		ef.i++;
	while (str[ef.i])
	{
		if (str[ef.i] == c)
			plus_row(str, &ef, c);
		else if (str[ef.i] == '\''
				|| str[ef.i] =='\\' || str[ef.i] == '\"')
			plus_i(str, &ef);
		else
			ef.i++;
	}
	if (str[ef.i - 1] != c)
		ef.row++;
	return (ef.row);
}

int	find_new_column(const char *str)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (check == 0 && (str[i] == '\''))
			check = 1;
		else if (check == 1 && (str[i] == '\''))
			break ;
		i++;
	}
	return (i - 1);
}

char	**malloc_free(char **new_str)
{
	size_t	i;

	i = 0;
	while (new_str[i])
	{
		free(new_str[i]);
		i++;
	}
	free(new_str);
	return (0);
}

size_t	find_column(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

size_t	ft_strlcpy_new_str1(char *dst, char const *src, size_t size)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	while (src[count] != '\0')
		count++;
	if (size != '\0')
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return ((size_t)count);
}


int	find_third_column(char *s)
{
	int	i;

	i = 0;
	s[0] = '\\';
	while (s[i])
		i++;
	s[i - 2] = '\\';
	s[i - 1] = '\"';
	return (i);
}

int	find_second_column(char *s)
{
	int		i;
	int		check;
	char	temp;

	check = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' && s[i + 1] == '\'')
		{
			temp = s[i];
			s[i] = s[i + 1];
			s[i + 1] = temp;
			i += 1;
		}
		else if (s[i] == '\'' && s[i + 1] == '\"')
		{
			temp = s[i];
			s[i] = s[i + 1];
			s[i + 1] = temp;
			i += 1;
		}
		i++;
	}
	return (i - 2);
}

int	check_all_line(char **s, char c)
{
	int	i;

	i = 0;
	if (**s == '\'' && *s[1] != '\"')
	{
		i = find_new_column(*s);
		(*s)++;
	}
	else if (**s == '\"' && *s[1] == '\'')
	{
		i = find_second_column(*s);
		s++;
	}
	else if (*s[0] == '\'' && *s[1] == '\"')
		i = find_third_column(*s);
	else
		i = find_column(*s, c);
	return (i);
}

void	oo(char *s, char c, char **new_str, int index[])
{
	while (index[2] < index[1])
	{
		while (*s && *s == c)
			s++;
		if (*s == '\'' && s[1] != '\"')
			index[0] = find_new_column(s++);
		else if (*s == '\"' && s[1] == '\'')
			index[0] = find_second_column(s++);
		else if (s[0] == '\'' && s[1] == '\"')
			index[0] = find_third_column(s);
		else
			index[0] = find_column(s, c);
		new_str[index[2]] = (char *)malloc(sizeof(char) * (index[0] + 1));
		if (!new_str[index[2]])
			malloc_free(new_str);
		ft_strlcpy_new_str1(new_str[index[2]++], s, index[0] + 1);
		if (index[2] < index[1])
			s += index[0];
	}
}

char	**ft_split2(char *s, char c)
{
	char	**new_str;
	int		index[3];

	if (s[0] == '\0')
		return (0);
	index[1] = check_row(s, c);
	new_str = (char **)malloc(sizeof(char *) * (index[1]) + 1);
	if (!new_str)
		return (0);
	index[2] = 0;
	oo (s, c, new_str, index);
	new_str[index[2]] = NULL;
	return (new_str);
}

//===========****===========****===========****===========****===========****===========****===========****===========****===========****===========****===========****//

char		*get_path(char **envp)
{
	int		i;
	int		j;
	char	find[5];

	i = 0;
	ft_strlcpy(find, "PATH", 5);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		if (ft_strncmp(find, envp[i], j) == 0)
			return (envp[i] + j + 1);
		++i;
	}
	return (NULL);
}

void terminal_msg()
{
	char buf[100];
	char *msg;

	msg = getcwd(buf, 100);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd(" $ ", 1);
}

void get_cmd(char **cmd)
{
	int i;

	i = 0;
	get_next_line(1, cmd);
}

int cmd_cd(char *cmd)
{
	char **strs;

	strs = ft_split(cmd, ' ');
	chdir(strs[1]);
	return (0);
}
//==============*==============*==============*==============*==============*==============*==============*==============*==============*//
char **plus_line(char **env, char *new_env)
{
    char **envp;
    int i;

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

//==============*==============*==============*==============*==============*==============*==============*==============*==============*//

char **cmd_export(char *cmd, char **envp)
{
    int i;
    char **path;

    path = ft_split2(cmd, ' ');
    if (!(ft_strcmp(cmd, "export")))
    {
        i = 0;
        while (1)
        {
            printf("%s\n",envp[i]);
            i++;
            if (!envp[i])
                break;
        }
    }
    else
    {
        envp = plus_line(envp, path[1]);
        i = 0;
        while (1)
        {
            printf("%s\n",envp[i]);
            i++;
            if (!envp[i])
                break;
        }
    }
    return (envp);
}

int run_cmd(char *cmd, char **envp)
{
	char **path;
	char **strs;
	char *tmp;
	pid_t pid;
	int i;

	if (!(ft_strcmp(cmd, "exit")))
		return (-1);
	if (!(ft_strncmp(cmd, "cd", 2)))
		return (cmd_cd(cmd));
    if (!(ft_strncmp(cmd, "export", 5)))
    {
        envp = cmd_export(cmd, envp);
        return (0);
    }
	pid = fork();
	i = 0;
	if (pid == 0)
	{
		path = ft_split2(get_path(envp), ':');
		strs = ft_split2(cmd, ' ');
		while (path[i])
		{
			tmp = ft_strjoin(path[i], "/");
			path[i] = tmp;
			tmp = ft_strjoin(path[i], *strs);
			execve(tmp, strs, envp);
			if (errno != ENOENT)
				perror("pipex:");
			free(tmp);
			i++;
		}
		ft_putstr_fd("pipex: command not found : ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		return (-1);
	}
	wait(&pid);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char *cmd;
	int i;

	i = 0;
	(void)av;
	(void)ac;
	while (1)
	{
		terminal_msg();
		get_cmd(&cmd);
		i = run_cmd(cmd, envp);
		if (i == -1)
			break ;
	}
}