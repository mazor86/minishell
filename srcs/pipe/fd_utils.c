/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:08:33 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/26 11:17:23 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_fds(t_all *all, int n)
{
	if (n == 0)
		dup2(0, all->save_fd[0]);
	else if (n == 1)
		dup2(1, all->save_fd[1]);
	else
	{
		all->save_fd[0] = dup(0);
		all->save_fd[1] = dup(1);
	}
}

void	restore_fds(t_all *all, int n)
{
	if (n == 0)
	{
		dup2(all->save_fd[0], 0);
		close(all->save_fd[0]);
	}
	else if (n == 1)
	{
		dup2(all->save_fd[1], 1);
		close(all->save_fd[1]);
	}
	else
	{
		dup2(all->save_fd[0], 0);
		dup2(all->save_fd[1], 1);
	}
}

void	close_pipe_fd(t_cmd *cmd)
{
	if (cmd->pipe == 1)
		close(cmd->fd_pipe[1]);
	if (cmd->prev && cmd->prev->pipe == 1)
		close(cmd->prev->fd_pipe[0]);
}
