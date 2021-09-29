#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"

typedef struct s_ef{
	size_t	row;
	size_t	i;
}				t_ef;

//---- main.c ---//
void terminal_msg();
char		*get_env(char **envp, char *option);

char **cmd_export(char *cmd, char **envp);
int cmd_env(char *cmd, char **envp);
char **plus_line(char **env, char *new_env);
int    print_export(char *str, char **envp);

char	**ft_split2(char *s, char c);
size_t	ft_strlcpy_new_str1(char *dst, char const *src, size_t size);
size_t	find_column(char const *s, char c);
char	**malloc_free(char **new_str);
int	find_new_column(const char *str);
int	check_row(char *str, char c);

void	plus_i(char *str, t_ef *ef);
void	plus_row(char *str, t_ef *ef, char c);
void	ef_init(t_ef *ef);

void path_free(char **str);
int is_quotes(char c);

// ------ signal.c -----//

void sighandler1(int sig);
void sighandler2(int sig);
void pipe_sighandler1(int sig);
void pipe_sighandler2(int sig);

// ----- pipe.c ------ //

int cmd_pipe(char *cmd, char **envp);


#endif