/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:07:42 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/12 20:15:57 by mazor            ###   ########.fr       */
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

void close_dup_fd(int red_in, int red_out, int n)
{
    if (n % 2 == 0)
        if (red_in > 0)
            close(red_in);
    if (n > 0)
        if (red_out > 0)
            close(red_out);
    if (n < 0)
    {
        if (red_out > 0)
            dup2(red_out, 1);
        if (red_in > 0)
            dup2(red_in, 0);
    }
}


int			init_redirect(t_all *all, t_cmd *cmd, int pipe)
{
	int		fd;
	int		fdin;
	int		fdout;
	int		i;
	int		n;

    fdin = -1;
    fdout = -1;
    if (cmd->redir->r[0] != '\0')
    {
        i = -1;
        n = count_redir(cmd->redir);
        while (++i < n)
        {
            if ((fd = open_file(cmd->redir[i].r, cmd->redir[i].file)) < 0)
            {
                close_dup_fd(fdin, fdout, 2);
                return (ft_error(cmd->redir[i].file, strerror(2), 2, all));
            }
            if (cmd->redir[i].r[0] == '>')
            {
                close_dup_fd(fdin, fdout, 1);
                fdout = fd;
            }
            else
            {
                close_dup_fd(fdin, fdout, 0);
                fdin = fd;
            }
        }
        close_dup_fd(fdin, fdout, -1);
    }
	pipe == 1 ? exec_command_pipe(all, &cmd) : exec_command(all, cmd);
    close_dup_fd(fdin, fdout, 2);
	return (all->exit_status);
}
