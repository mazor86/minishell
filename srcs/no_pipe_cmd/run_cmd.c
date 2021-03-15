/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 20:15:57 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** clears strings created for the execve
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			free_local(char **array_1, char **array_2, char **text, int ret)
{
	if (array_1)
		free_array(array_1);
	if (array_2)
		free_array(array_2);
	if (*text)
	{
		free(*text);
		*text = NULL;
	}
	return (ret);
}

/*
** checks if it is a build in or external command and starts
** the corresponding execution
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			exec_command(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	if ((res_cmd = start_cmd(all, cmd)) > 0)
		return (all->exit_status);
	if (res_cmd == -1)
		start_execve(all, cmd);
	return (all->exit_status);
}

/*
** select the last of the corresponding type redirections,
** opening the files while it dont get to the last
**
** variables: redir_type - the fdin or fdout, redir - type of redirection
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			redir_execute(t_all *all, t_cmd *lst, char redir, int *redir_type)
{
	int i;
	int fd;

	i = 0;
	while (lst->redir[i].r[0] != '\0')
	{
		if (lst->redir[i].r[0] == redir)
		{
			fd = open_file(lst->redir[i].r, lst->redir[i].file);
			if (*redir_type > 0)
				close(*redir_type);
			if (fd < 0)
			{
				restore_fds(all);
				return (ft_error(lst->redir[i].file, strerror(2), 2, all));
			}
			*redir_type = fd;
		}
		i++;
	}
	return (0);
}

/*
** checks for redirections and applys to the corresponding
** type of stream: input or output. If there are no redirections,
** apply the saved stdin or stdout
**
** variables: fd - the fdin or fdout, redir - type of redirection
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			redirections(t_all *all, t_cmd *lst, int *fd, char redir)
{
	if (lst->redir->r[0] != '\0')
	{
		if (redir_execute(all, lst, redir, fd) != 0)
			return (all->exit_status);
	}
	if (*fd < 0)
	{
		if (redir == '<')
			*fd = dup(all->save_fd[0]);
		else
			*fd = dup(all->save_fd[1]);
	}
	return (0);
}

/*
** execute the command
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int			run_cmd(t_all *all)
{
	t_cmd	*lst;
	int		fdin;
	int		fdout;

	lst = all->cmd;
	fdin = -1;
	fdout = -1;
	save_fds(all);
	if (!is_null_cmd(lst) || lst->redir->r[0] != '\0')
	{
		if (lst->pipe == 1)
			exec_command_pipe(all, &lst);
		else
		{
			if (redirections(all, lst, &fdin, '<') == 0 &&
			redirections(all, lst, &fdout, '>') == 0 &&
			close_dup2_closer(all, fdin, 0) == 0 &&
			close_dup2_closer(all, fdout, 1) == 0 &&
			!is_null_cmd(lst))
			{
				exec_command(all, lst);
			}
			else
			{
				if (fdin >= 0)
				{
					close(fdin);
					fdin = -1;
				}
				if (fdout >= 0)
				{
					close(fdout);
					fdout = -1;
				}
			}
			restore_fds(all);
		}
		//restore_fds(all);
	}
	return (all->exit_status);
}
