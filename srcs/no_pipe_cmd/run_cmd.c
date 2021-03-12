/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by mazor             #+#    #+#             */
/*   Updated: 2021/02/26 18:24:37 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** clears strings
**
** @param **split array of strings
** @param **split2 array of strings
** @param **text pointer to string
** @param ret return
** @return ret
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
** execute the execve command
**
** @param *all general structure
** @param *lst command pointer
** @param **envp array of environment variables strings
** @param **argv array of argument strings
** @return 0 if good, otherwise -1
*/

void		parent_process(int pid, t_all *all, t_cmd *lst)
{
	mute_signals();
	waitpid(pid, &all->res, 0);
	catch_signals(all);
	implement_signals(all);
	close_pipe_fd(lst);
}

int		child_process(t_all *all, char **envp, char **argv, char *fullname)
{
	init_signals(all, 'c');
	errno = 0;
	all->exit_status = 0;
	if (execve(fullname, argv, envp) == -1)
		all->exit_status = errno;
	return (all->exit_status);
}

int			start_execve(t_all *all, t_cmd *lst)
{
	pid_t		pid;
	char		*fullname;
	char		**envp;
	char		**argv;

	all->exit_status = 0;
	envp = deconvert_env(&all->my_env);
	argv = convert_argv(lst);
	fullname = get_full_cmd_name(all, lst);
	if (envp && argv && fullname)
	{
		if ((pid = fork()) == -1)
		{
			ft_error(lst->name, "failed to fork", 13, all);
		}
		else if (pid == 0)
		{
			child_process(all, envp, argv, fullname);
			exit(ft_error(lst->name, strerror(errno), errno, all));
		}
		else
			parent_process(pid, all, lst);
		init_signals(all, 'p');
	}
	return (free_local(envp, argv, &fullname, all->exit_status));
}

int exec_command(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	if ((res_cmd = start_cmd(all, cmd)) > 0)
		return (all->exit_status);
	if (res_cmd == -1)
		start_execve(all, cmd);
	return (all->exit_status);
}


int		redir_execute(t_all *all, t_cmd *lst, char redir, int *red_type)
{
	int i;
	int fd;

	i = 0;
	while (lst->redir[i].r[0] != '\0')
	{
		if (lst->redir[i].r[0] == redir)
		{
			fd = open_file(lst->redir[i].r, lst->redir[i].file);
			if (*red_type > 0)
				close(*red_type);
			if (fd < 0)
			{
				restore_fds(all);
				return (ft_error(lst->redir[i].file, strerror(2), 2, all));
			}
			*red_type = fd;
		}
		i++;
	}
	return (0);
}

int redirections(t_all *all, t_cmd *lst, int *fd, char redir)
{
	if (lst->redir->r[0] != '\0') {
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
** @param *all general structure
** @return 0 if good, otherwise returns exit status and prints error
*/

int			run_cmd(t_all *all)
{
	t_cmd	*lst;
	int 	fdin;
	int 	fdout;

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
			dup2_closer(all, fdin, 0) == 0 &&
			dup2_closer(all, fdout, 1) == 0 &&
			!is_null_cmd(lst))
				exec_command(all, lst);
		}
	}
	restore_fds(all);
	return (all->exit_status);
}
