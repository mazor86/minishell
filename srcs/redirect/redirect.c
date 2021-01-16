/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:07:42 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/17 04:08:39 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char redir[2], char *argum)
{
	int fd;

	if (redir[0] == '<')
		fd = open(argum, O_RDONLY, S_IRWXU);
	else
	{
		if (redir[0] == '>')
			fd = open(argum, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		else
			fd = open(argum, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	}
	return (fd);
}

int	init_redirect(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
	t_cmd	*temp;
	int		fd;

	temp = cmd;
	while (temp->redir[0] != '\0' && temp->next)
	{
		temp->redir[0] == '<' ? save_fds(all, 0) : save_fds(all, 1);
		while (ft_strcmp(temp->redir, cmd->redir) == 0)
		{
			fd = open_file(temp->redir, temp->argv[0]);
			if (ft_strcmp(temp->next->redir, cmd->redir) == 0)
			{
				close(fd);
				temp = temp->next;
			}
		}
		if (exec_command(all, cmd, envp, argv) != 0)
		{
			temp->redir[0] == '<' ? restore_fds(all, 0) : restore_fds(all, 1);
			return (all->exit_status);
		}
		temp->redir[0] == '<' ? restore_fds(all, 0) : restore_fds(all, 1);
		temp = temp->next;
	}
	return (all->exit_status);
}
