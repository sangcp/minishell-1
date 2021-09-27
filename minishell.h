#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_ef{
	size_t	row;
	size_t	i;
}				t_ef;

char **cmd_export(char *cmd, char **envp);
char **plus_line(char **env, char *new_env);

char	**ft_split2(char *s, char c);
size_t	ft_strlcpy_new_str1(char *dst, char const *src, size_t size);
size_t	find_column(char const *s, char c);
char	**malloc_free(char **new_str);
int	find_new_column(const char *str);
int	check_row(char *str, char c);

void	plus_i(char *str, t_ef *ef);
void	plus_row(char *str, t_ef *ef, char c);
void	ef_init(t_ef *ef);

#endif