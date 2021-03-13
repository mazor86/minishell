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

void	save_fds(t_all *all)
{
	all->save_fd[0] = dup(0);
	all->save_fd[1] = dup(1);
}

int dup2_closer(t_all *all, int fd, int std)
{
    if (dup2(fd, std) < 0)
    {
        close(fd);
        return (ft_error("dup2", strerror(errno), errno, all));
    }
    close(fd);
    return (0);
}

void	restore_fds(t_all *all)
{
	{
        dup2_closer(all, all->save_fd[0], 0);
        dup2_closer(all, all->save_fd[1], 1);
    }
}

void	close_pipe_fd(t_cmd *cmd)
{
	if (cmd->pipe == 1)
	{
        close(cmd->fd_pipe[1]);
    }
	if (cmd->prev && cmd->prev->pipe == 1)
	{
		close(cmd->prev->fd_pipe[0]);
	}
}
