/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:08:33 by tisabel           #+#    #+#             */
/*   Updated: 2021/02/26 18:16:47 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_fds(t_all *all, int n)
{
//	if (n == 0)
//		dup2(0, all->save_fd[0]);
//	else if (n == 1)
//		dup2(1, all->save_fd[1]);
//	else
    n;
	{
		all->save_fd[0] = dup(0);
		all->save_fd[1] = dup(1);
	}
}
int dup2_closer(int fd, int std)
{
    if (dup2(fd, std) <0)
    {
        close(fd);
        //todo return error
        return (1);
    }
    close(fd);
    return (0);
}
void	restore_fds(t_all *all, int n)
{
//	if (n == 0)
//	{
//		dup2(all->save_fd[0], 0);
//		close(all->save_fd[0]);
//	}
//	else if (n == 1)
//	{
//		dup2(all->save_fd[1], 1);
//		close(all->save_fd[1]);
//	}
//	else
	{
        dup2_closer(all->save_fd[0], 0);
        dup2_closer(all->save_fd[1], 1);
    }
}

void	close_pipe_fd(t_cmd *cmd)
{
	if (cmd->next->pipe == 0 && cmd->pipe == 1)
	{
        close(cmd->fd_pipe[1]);
    }
	if (cmd->prev && cmd->prev->pipe == 1)
	{
		close(cmd->prev->fd_pipe[0]);
	}
}
