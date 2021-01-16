
#include "../includes/minishell.h"

void sigint_sighandler(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \n", 1);
}

void sigquit_sighandler(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void init_signals(t_all *all)
{
	signal(SIGINT, sigint_sighandler);
	signal(SIGQUIT, sigquit_sighandler);
}
