/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/12 17:21:18 by mazor            ###   ########.fr       */
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
			return (ft_error(cmd->name, "permission denied", 13, all));
    }
	return (free_local(envp, argv, &fullname, all->exit_status));
}

void	run_command_pipe(t_all *all, t_cmd *cmd)
{
	int res_cmd;

    res_cmd = start_cmd(all, cmd);
	if (res_cmd < 0)
	    all->exit_status = execve_with_pipe(all, cmd);
	exit(all->exit_status);
}

void pipe_fd(t_cmd *lst, int *fdin, int *fdout)
{
	pipe(lst->fd_pipe);
	*fdout = lst->fd_pipe[1];
	*fdin = lst->fd_pipe[0];
}

int init_pipes_redir(t_all *all, t_cmd **lst)
{
    t_cmd *tmp;
	int fdin;
	int fdout;

	fdin = -1;
	fdout = -1;
    tmp = *lst;
    while (tmp)
    {
		redirections(all, *lst, &fdin, '<');
        if (tmp->pipe != 0)
        {
            if (dup2_closer(all, fdin, 0) != 0)
				return (all->exit_status);
			pipe_fd(tmp, &fdin, &fdout);
        }
        else if (tmp->pipe == 0)
        {
            if (close(fdin) != 0)
				return (errno);
			redirections(all, *lst, &fdout, '<');
        }
        dup2_closer(all, fdout, 1);
    }
    return (0);
}

void    pipe_parent_process(t_all *all, int pipes_len)
{
    int i;

    i = 0;
    mute_signals();
    while (i < pipes_len)
    {
        waitpid(all->pid[i], &all->res, 0);
        i++;
    }
    init_signals(all, 'p');
}

void    close_pipe_fds(t_cmd **lst)
{
    t_cmd *tmp;

    tmp = *lst;
    while (tmp->prev && tmp->prev->pipe)
    {
        close(tmp->fd_pipe[1]);
        close(tmp->fd_pipe[0]);
        tmp = tmp->next;
    }
}

int     exec_command_pipe(t_all *all, t_cmd **lst)
{
    int i;

    i = 0;
    while (*lst)
    {
    	if (!is_null_cmd(*lst) || (*lst)->redir->r[0] != '\0')
    	{
			if (init_pipes_redir(all, lst) != 0)
				return (all->exit_status);
            all->pid[i] = fork();
            if (all->pid[i] < 0)
                return (ft_error((*lst)->name, "failed to fork", 13, all));
            if (all->pid[i] == 0)
            {
                init_signals(all, 'c');
                run_command_pipe(all, *lst);
            }
			if ((*lst)->next == NULL)
				break ;
			*lst = (*lst)->next;
			i++;
		}
    }
    pipe_parent_process(all, i);
    close_pipe_fds(lst);
    return (all->exit_status);
}
