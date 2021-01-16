/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:08:33 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/17 04:08:58 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_fds(t_all *all, int n)
{
	if (n == 0)
	{
		dup2(0, all->save_fd[0]);
		close(0);
	}
	else if (n == 1)
	{
		dup2(1, all->save_fd[1]);
		close(1);
	}
	else
	{
		dup2(0, all->save_fd[0]);
		dup2(1, all->save_fd[1]);
		close(0);
		close(1);
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
		close(all->save_fd[0]);
		close(all->save_fd[1]);
	}
}
