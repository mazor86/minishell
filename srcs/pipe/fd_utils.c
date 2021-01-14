
#include "../includes/minishell.h"

void save_fds(t_all *all)
{
	dup2(all->fd[0], 0);
	dup2(all->fd[1], 1);
	close(all->fd[0]);
	close(all->fd[1]);
}
