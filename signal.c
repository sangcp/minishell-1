#include "minishell.h"

void pipe_sighandler1(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void pipe_sighandler2(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		signal(SIGQUIT, sighandler2);
	}
}

void sighandler1(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		terminal_msg();
		signal(SIGINT, sighandler1);
	}
}

void sighandler2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		signal(SIGINT, sighandler2);
	}
}
