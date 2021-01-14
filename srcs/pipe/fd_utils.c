
#include "../includes/minishell.h"

void save_fds(t_all *all)
{
	dup2(0, all->save_fd[0]);
	dup2(1, all->save_fd[1]);
	close(0);
	close(1);
}

void restore_fds(t_all *all)
{
	dup2(all->save_fd[0], 0);
	dup2(all->save_fd[1], 1);
	close(all->save_fd[0]);
	close(all->save_fd[1]);
}
