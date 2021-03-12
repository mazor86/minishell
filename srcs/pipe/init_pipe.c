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

//int init_pipes_redir(t_all *all, t_cmd **lst, int *fdin, int *fdout)
//{
////    redirections(all, *lst, fdin, '<');
////    redirections(all, *lst, fdout, '<');
//    if ((*lst)->prev == NULL)
//        *fdin = dup(all->save_fd[0]);
//    if ((*lst)->pipe == 1)
//    {
//        pipe((*lst)->fd_pipe);
//        dup2_closer(all, (*lst)->fd_pipe[1], 1);
//
//    }
//}

/*
int init_pipes_redir(t_all *all, t_cmd **lst, int *fdin, int *fdout)
{
	int fdin;
	int fdout;

    fdin = -1;
    fdout = -1;
    redirections(all, *lst, &fdin, '<');
    if ((*lst)->pipe != 0)
    {
        if (dup2_closer(all, fdin, 0) != 0)
            return (all->exit_status);
        pipe_fd(*lst, &fdin, &fdout);
    }
    else if ((*lst)->pipe == 0)
    {
        if (close(fdin) != 0)
            return (errno);
        redirections(all, *lst, &fdout, '<');
    }
    dup2_closer(all, fdout, 1);
    return (0);
}*/

void pipe_parent_process(t_all *all, int pipes_len)
{
    int i;

    i = 0;
    mute_signals();
    while (i <= pipes_len)
    {
//        ft_putstr_fd("!!!!", 2);
//        ft_putnbr_fd( all->pid[i], 2);
//        ft_putstr_fd("----\n", 2);
        waitpid(all->pid[i], &all->res, 0);
        i++;
    }
    while (all->pid[i] != 0 && i < PID_SIZE)
    {
        all->pid[i] = 0;
        i++;
    }
    init_signals(all, 'p');
}

int     exec_command_pipe(t_all *all, t_cmd **lst)
{
    int i;
    int fdin;
    int fdout;

    fdin = -1;
    fdout = -1;
    i = 0;
    while (*lst)
    {
    	if (!is_null_cmd(*lst) || (*lst)->redir->r[0] != '\0')
    	{
			//if (init_pipes_redir(all, lst, &fdin, &fdout) != 0)
			//	return (all->exit_status);
			if ((*lst)->pipe == 1)
			    pipe((*lst)->fd_pipe);
            all->pid[i] = fork();
            if (all->pid[i] < 0)
                return (ft_error((*lst)->name, "failed to fork", 13, all));
            if (all->pid[i] == 0)
            {
//                if (i > 0)
//                    waitpid(all->pid[i - 1], &all->res, 0);
//                ft_putstr_fd("child ", 2); //
//                ft_putnbr_fd(i, 2); //
//                ft_putstr_fd("\n", 2); //
//                if (all->last_fd > 0) {
//                    dup2(all->last_fd, 0);
//                    close(all->last_fd);
//                    //char *buff;
//                    //get_next_line(all->last_fd, &buff, all);
//                    //ft_putstr_fd("PRINT: ", 2);
//                   // ft_putstr_fd(buff,2);
//                   // ft_putstr_fd("PRINT: ", 2);
//                }
                close(1);
                if ((*lst)->pipe == 1)
                {
                    dup2_closer(all, (*lst)->fd_pipe[1], 1);
                    close((*lst)->fd_pipe[0]);
                }
                else
                    dup2(all->save_fd[1], 1);
                init_signals(all, 'c');
                run_command_pipe(all, *lst);
            }
            if (all->pid[i] > 0)
            {
                ft_putstr_fd("----", 2);
                ft_putnbr_fd( all->pid[i], 2);
                ft_putstr_fd("----\n", 2);
//                if (all->last_fd > 0)
//                    close(all->last_fd);
//                all->last_fd = -1;
                close(0);
                if ((*lst)->pipe == 1)
                {
                    close((*lst)->fd_pipe[1]);
                    dup2((*lst)->fd_pipe[0], 0);
                    close((*lst)->fd_pipe[0]);
                }
                else
                    dup2(all->save_fd[0], 0);
            }
			if ((*lst)->next == NULL)
				break ;
			*lst = (*lst)->next;
			i++;
		}
    }
    pipe_parent_process(all, i);
    return (all->exit_status);
}
