/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by mazor             #+#    #+#             */
/*   Updated: 2021/01/26 11:11:31 by tisabel          ###   ########.fr       */
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

void        parant_process(int pid, t_all *all, t_cmd *lst)
{
    mute_signals();
    waitpid(pid, &all->res, 0);
    catch_signals(all);
    implement_signals(all);
    close_pipe_fd(lst);
}

int			start_execve(t_all *all, t_cmd *lst)
{
	pid_t		pid;
	char		*fullname;
	extern int	errno;
    char        **envp;
    char        **argv;

	all->exit_status = 0;
    envp = deconvert_env(&all->my_env);
    argv = convert_argv(lst);
    fullname = get_full_cmd_name(all, lst);
    if (!envp ||!argv || !fullname)
        return (free_local(envp, argv, &fullname, all->exit_status));
	if ((pid = fork()) == -1)
		return (ft_error(lst->name, ": failed to fork", 13, all));
	if (pid == 0)
	{
		init_signals(all, 'c');
		errno = 0;
		if (execve(fullname, argv, envp) == -1)
			ft_error(lst->name, strerror(errno), errno, all);
		exit(all->exit_status);
	}
	else
        parant_process(pid, all, lst);
	init_signals(all, 'p');
	return (free_local(envp, argv, &fullname, all->exit_status));
}

int			exec_command(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	if (cmd->prev && cmd->prev->pipe == 1 &&
		(dup2(cmd->prev->fd_pipe[0], 0) < 0))
		return (all->exit_status);
	if (cmd->prev && cmd->prev->pipe == 1)
	{
		close(cmd->prev->fd_pipe[0]);
		restore_fds(all, 1);
	}
	if ((res_cmd = start_cmd(all, cmd)) > 0)
		return (all->exit_status);
	if (res_cmd == -1)
		start_execve(all, cmd);
	return (all->exit_status);
}

/*
** execute the command
**
** @param *all general structure
** @return 0 if good, otherwise returns exit status and prints error
*/

int			parser_cmd(t_all *all)
{
	t_cmd	*lst;

	lst = all->cmd;
	if (parser_syntax_errors(all) == 1)
		return (all->exit_status);
	while (lst)
	{
		if (!is_null_cmd(lst) || lst->redir->r[0] != '\0')
		{
			if (lst->pipe == 1)
			{
				if (with_pipe(all, lst) != 0)
					return (all->exit_status);
			}
			else
			{
				if (no_pipe(all, lst) != 0)
					return (all->exit_status);
			}
		}
		lst = lst->next;
	}
	return (all->exit_status);
}
