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

int execve_with_pipe(t_all *all, t_cmd *cmd)
{
	char	*fullname;
    char    **argv;
    char    **envp;

	all->exit_status = 0;
    envp = deconvert_env(&all->my_env);
    argv = convert_argv(cmd);
    fullname = get_full_cmd_name(all, cmd);
	if (envp && argv && fullname)
    {
        if (execve(fullname, argv, envp) == -1)
            exit(ft_error(cmd->name, "permission denied", 13, all));
        exit(free_local(envp, argv, &fullname, 0));
    }
    exit(free_local(envp, argv, &fullname, all->exit_status));
}

void	run_command_pipe(t_all *all, t_cmd *cmd)
{
	int res_cmd;

//	if (cmd->prev && cmd->prev->pipe == 1 &&
//		(dup2(cmd->prev->fd_pipe[0], 0) < 0))
//	{
//	    close(cmd->prev->fd_pipe[0]);
//	    exit(all->exit_status);
//	}
//    close(cmd->prev->fd_pipe[0]);
    res_cmd = start_cmd(all, cmd);
	if (res_cmd < 0)
	    all->exit_status = execve_with_pipe(all, cmd);
	exit(all->exit_status);
}

int     init_pipes_redir(t_all *all, t_cmd **lst, int redin, int redout)
{
    int	other_ret;
    t_cmd *tmp;

    other_ret = 0;
    tmp = *lst;
    while (tmp)
    {
        if (tmp->redir->r[0] != '\0')
            redir_execute(all, tmp, '<', &redin);
        if (redin < 0)
            redin = dup(all->save_fd[0]);
        if (tmp->pipe != 0)
        {
            dup2_closer(all, redin, 0);
            pipe(tmp->fd_pipe);
            redout = tmp->fd_pipe[1];
            redin = tmp->fd_pipe[0];
        }
        else if (tmp->pipe == 0)
        {
            close(redin);
            if (tmp->redir->r[0] != '\0')
                redir_execute(all, tmp, '>', &redout);
            else
                redout = dup(all->save_fd[1]);
        }
        if (redout < 0)
            redout = dup(all->save_fd[1]);
        dup2_closer(all, redout, 1);
        if (tmp->pipe == 0 && !(tmp->prev && tmp->prev->pipe == 1))
            other_ret = start_cmd(all, tmp);
        if (other_ret > 0)
            return (all->exit_status);
    }
    return (all->exit_status);
}

int		exec_command_pipe(t_all *all, t_cmd **lst)
{
    int redin;
    int redout;
    int i;
    pid_t pid[PID_SIZE];

    redin = -1;
    redout = -1;
    i = 0;
    while (*lst)
    {
        if (init_pipes_redir(all, lst, redin, redout) != 0)
            return (all->exit_status);
        if ((*lst)->pipe == 1 || ((*lst)->prev && (*lst)->prev->pipe == 1))
        {
            pid[i] = fork();
            if (pid[i] < 0)
                return (ft_error((*lst)->name, "failed to fork", 13, all));
            if (pid[i] == 0)
            {
                printf("child");
                init_signals(all, 'c');
                run_command_pipe(all, *lst);
            }
            if (pid[i] > 0)
            {
                mute_signals();
                waitpid(pid[i], &all->res, 0);
            }
        }
        if ((*lst)->next == NULL)
            break;
        *lst = (*lst)->next;
    }
    if (*lst && (*lst)->pipe == 1 && (*lst)->prev && (*lst)->prev->pipe == 1)
    {
        while ((*lst)->prev && (*lst)->prev->pipe)
        {
            close((*lst)->fd_pipe[1]);
            close((*lst)->fd_pipe[0]);
        }
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
