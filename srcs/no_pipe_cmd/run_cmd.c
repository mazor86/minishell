/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 23:53:30 by mazor            ###   ########.fr       */
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
** support functions for <start_execve> that run the child and parant process activities
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

static void	parent_process(int pid, t_all *all, t_cmd *lst)
{
	mute_signals();
	waitpid(pid, &all->res, 0);
	catch_signals(all);
	implement_signals(all);
	close_pipe_fd(lst);
}

static int	child_process(t_all *all, char **envp, char **argv, char *fullname)
{
	init_signals(all, 'c');
	errno = 0;
	all->exit_status = 0;
	if (execve(fullname, argv, envp) == -1)
		all->exit_status = errno;
	return (all->exit_status);
}

/*
** converts environmental variables to the array, checks if the
** command exists and runs the corresponding command
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

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

/*
** checks if it is a build in or external command and starts
** the corresponding execution
**
** return: 0 if good, otherwise returns exit status of the failed command
*/

int exec_command(t_all *all, t_cmd *cmd)
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

int		redir_execute(t_all *all, t_cmd *lst, char redir, int *redir_type)
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
** return: 0 if good, otherwise returns exit status of the failed command
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
