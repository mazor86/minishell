/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/02/26 15:53:39 by mazor            ###   ########.fr       */
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
		exit(ft_error(cmd->name, "permission denied", 13, all));
	free_local(envp, argv, &fullname, 0);
	exit(0);
}

void	run_command_pipe(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	if (cmd->prev && cmd->prev->pipe == 1 &&
		(dup2(cmd->prev->fd_pipe[0], 0) < 0))
	{
	    close(cmd->prev->fd_pipe[0]);
	    exit(all->exit_status);
	}
    close(cmd->prev->fd_pipe[0]);
	if ((res_cmd = start_cmd(all, cmd)) > 0)
		exit(all->exit_status);
	if (res_cmd == -1)
		execve_with_pipe(all, cmd, NULL, NULL);
	exit(0);
}

int		exec_command_pipe(t_all *all, t_cmd **lst)
{
    int redin;
    int redout;
    int	other_ret;
    pid_t pid;

    redin = -1;
    redout = -1;
    other_ret = 0;
    while (*lst) {
        if ((*lst)->redir->r[0] != '\0')
            redir_execute(all, *lst, '<', &redin);
        if (redin < 0)
            redin = dup(all->save_fd[0]);
        if ((*lst)->pipe != 0) {
            dup2_closer(all, redin, 0);
            pipe((*lst)->fd_pipe);
            redout = (*lst)->fd_pipe[1];
            redin = (*lst)->fd_pipe[0];
        } else if ((*lst)->pipe == 0) {
            close(redin);
            if ((*lst)->redir->r[0] != '\0')
                redir_execute(all, *lst, '>', &redout);
            else
                redout = dup(all->save_fd[1]);
        }
        if (redout < 0)
            redout = dup(all->save_fd[1]);
        dup2_closer(all, redout, 1);
        if ((*lst)->pipe == 0 && !((*lst)->prev && (*lst)->prev->pipe == 1))
            other_ret = start_cmd(all, *lst);
        if (other_ret > 0)
            return (all->exit_status);
        if ((*lst)->pipe == 1 || ((*lst)->prev && (*lst)->prev->pipe == 1)) {
            pid = fork();
            if (pid < 0)
                return (ft_error((*lst)->name, "failed to fork", 13, all));
            if (pid == 0) {
                printf("child"); //
                init_signals(all, 'c');
                run_command_pipe(all, *lst);
            }
            if (pid > 0) {
                mute_signals();
                waitpid(pid, &all->res, 0);
            }
        }
        if ((*lst)->next == NULL)
            break;
        *lst = (*lst)->next;
    }
    if (*lst && (*lst)->pipe == 1 && (*lst)->prev && (*lst)->prev->pipe == 1)
        while ((*lst)->prev && (*lst)->prev->pipe)
        {
            close((*lst)->fd_pipe[1]);
            close((*lst)->fd_pipe[0]);
        }
    //all->exit_status = errno;
    init_signals(all, 'p');
    return (all->exit_status);
}

/*
int		exec_command_pipe(t_all *all, t_cmd *cmd)
{
	pid_t		pid;
	extern int	errno;

	errno = 0;
	pipe(cmd->fd_pipe);
	if ((pid = fork()) == -1)
		return (ft_error(cmd->name, "failed to fork", 13, all));
	if (pid == 0)
	{
		dup2(cmd->fd_pipe[1], 1);
		close(cmd->fd_pipe[1]);
		init_signals(all, 'c');
		run_command_pipe(all, cmd);
	}
	else
	{
		mute_signals();
		waitpid(pid, &all->res, 0);
		//close_pipe_fd(cmd);
	}
	all->exit_status = errno;
	init_signals(all, 'p');
	return (all->exit_status);
}*/
