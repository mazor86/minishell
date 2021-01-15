
#include "../includes/minishell.h"

int with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
	int res_cmd;
	pid_t childpid;

	pipe(all->pipe_fd);
	if ((childpid = fork()) == -1)
		ft_error("fork", "return -1", 12, all);
	if (childpid == 0)
		close(all->pipe_fd[0]);
	else
		close(all->pipe_fd[1]);
	exec_command(all, cmd, envp, argv);
	return (all->exit_status);
}
