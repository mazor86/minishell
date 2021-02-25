/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:07:42 by tisabel           #+#    #+#             */
/*   Updated: 2021/02/25 19:23:07 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			open_file(char redir[2], char *argum)
{
	int fd;

	if (redir[0] == '<')
		fd = open(argum, O_RDONLY, S_IRWXU);
	else
	{
		if (redir[1] == '>')
			fd = open(argum, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		else
			fd = open(argum, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	}
	return (fd);
}

int			count_redir(t_redir *redir)
{
	int i;

	i = 0;
	while (redir[i].r[0] != '\0')
		i++;
	return (i);
}

void		close_fds(int *fds, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		close(fds[i]);
		i++;
	}
}

//static int	change_redir(t_cmd *cmd, char **redir, int i, int fd)
//{
//	if (cmd->redir[i].r[0] == cmd->redir[0].r[0])
//	{
//		(*redir)[0] = cmd->redir[i].r[0];
//		(*redir)[1] = cmd->redir[i].r[1];
//		return (1);
//	}
//	else if (cmd->redir[i].r[0] != cmd->redir[0].r[0] &&
//		cmd->redir[i].r[0] != '\0')
//		close(fd);
//	return (0);
//}


int			init_redirect(t_all *all, t_cmd *cmd, int pipe)
{
	int		fd;
	int		red_in;
	int		red_out;
	int		i;
	int		n;

	i = -1;
	red_in = 0;
	red_out = 0;
	n = count_redir(cmd->redir);
	while (++i < n)
	{
		if ((fd = open_file(cmd->redir[i].r, cmd->redir[i].file)) < 0)
		{
			if (red_in > 0)
				close(red_in);
			if (red_out > 0)
				close(red_out);
			return (ft_error(cmd->redir[i].file, strerror(2), 2, all));
		}
		if (cmd->redir[i].r[0] == '>')
		{
			if (red_out > 0)
				close(red_out);
			red_out = fd;
		}
		else
		{
			if (red_in > 0)
				close(red_in);
			red_in = fd;
		}
	}
	if (red_out != 0)
		dup2(red_out, 1);
	if (red_in != 0)
		dup2(red_in, 0);
	pipe == 1 ? exec_command_pipe(all, cmd) : exec_command(all, cmd);
	if (red_in > 0)
		close(red_in);
	if (red_out > 0)
		close(red_out);
	return (all->exit_status);
}
