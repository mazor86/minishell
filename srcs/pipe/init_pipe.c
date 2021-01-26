/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/26 11:34:11 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execve_with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
	char	*fullname;

	fullname = NULL;
	all->exit_status = 0;
	if (!(envp = deconvert_env(&all->my_env)) ||
		!(argv = convert_argv(cmd)))
		return (free_local(envp, argv, &fullname, -1));
	if (!(fullname = get_full_cmd_name(all, cmd)))
		return (free_local(envp, argv, &fullname, 0));
	if (execve(fullname, argv, envp) == -1)
		exit(ft_error(cmd->name, ": permission denied", 13, all));
	free_local(envp, argv, &fullname, 0);
	exit(0);
}

void	run_command_pipe(t_all *all, t_cmd *cmd)
{
    int res_cmd;

	if (cmd->prev && cmd->prev->pipe == 1 &&
		(dup2(cmd->prev->fd_pipe[0], 0) < 0))
		exit(all->exit_status);
	if ((res_cmd = start_cmd(all, cmd)) > 0)
		exit(all->exit_status);
	if (res_cmd == -1)
		execve_with_pipe(all, cmd, NULL, NULL);
	exit(0);
}

int		exec_command_pipe(t_all *all, t_cmd *cmd)
{
	pid_t		pid;
	extern int	errno;

	errno = 0;
	pipe(cmd->fd_pipe);
	if ((pid = fork()) == -1)
		return (ft_error(cmd->name, ": failed to fork", 13, all));
	if (pid == 0)
	{
		dup2(cmd->fd_pipe[1], 1);
		init_signals(all, 'c');
		run_command_pipe(all, cmd);
	}
	else
	{
		mute_signals();
		waitpid(pid, &all->res, 0);
		close_pipe_fd(cmd);
	}
	all->exit_status = errno;
	init_signals(all, 'p');
	return (all->exit_status);
}

int		with_pipe(t_all *all, t_cmd *cmd)
{
	if (cmd->redir->r[0] != '\0')
	{
		if (init_redirect(all, cmd, 1) != 0)
			return (all->exit_status);
	}
	else
	{
		if (exec_command_pipe(all, cmd) != 0)
			return (all->exit_status);
	}
	return (all->exit_status);
}
