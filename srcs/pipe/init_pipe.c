
#include "../includes/minishell.h"

<<<<<<< HEAD
int with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp) {
=======
int with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
>>>>>>> master
	int res_cmd;
	pid_t childpid;

	pipe(all->pipe_fd);
	if ((childpid = fork()) == -1)
		ft_error("fork", "return -1", 12, all);
	if (childpid == 0)
		close(all->pipe_fd[0]);
	else
		close(all->pipe_fd[1]);
	if ((res_cmd = start_cmd(all, cmd)) != 0)
		return (all->exit_status);
	if (!res_cmd) {
		if (start_execve(all, cmd, envp, argv) != 0)
			return (all->exit_status);
		return (0);
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> master
