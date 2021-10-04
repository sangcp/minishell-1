#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
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

// ---

typedef struct s_ops
{
	char			*operation;
	char			**args;
	int				in_quotes;
	int				rv;
	char			type;
	int				fds[2];
	struct s_ops	*next;
	struct s_ops	*prev;
}					t_ops;

typedef struct s_shell
{
	t_list			*ops;
	char			**args;
	char			**evs;
	int				rv;
	int				fds[2];
	int				prev_pipe;
	int				count;
	int				stdinp;
	int				stdout;
}					t_shell;

//---- main.c ---//
void terminal_msg();
char		*get_env(char **envp, char *option);
void get_cmd(char **cmd);

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

// ----- parse.c ---- //

t_list *parse(t_shell *mini, char *cmd);

// ----- run_cmd.c --- //
int run_cmd1(t_shell *mini, t_list *list);
int	shell_execute(t_shell *mini, char **args);

// ----- operator.c ---//
int	operator_redirect_input(t_list *tlist, t_shell *shell);
int	operator_append_output(t_list *tlist, t_shell *shell);
int	operator_redirect_output(t_list *tlist, t_shell *shell);
#endif