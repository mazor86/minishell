
#include "../includes/minishell.h"

int init_pipe(t_all *all, t_cmd *cmd)
{
	pid_t   childpid;

	pipe(all->pipe_fd);
	if ((childpid = fork()) == -1)
		ft_error("fork", "return -1", 12, all);
	if (childpid == 0)
		close (all->pipe_fd[0]);
	else
		close (all->pipe_fd[1]);
	return (0);
}

