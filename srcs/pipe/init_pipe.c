/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/25 20:21:41 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** function pointers initialization
**
** @param **f a pointer to an array of functions
*/

static void	init_f(int (**f)(t_all*, t_cmd*))
{
    f[0] = ft_echo;
    f[1] = ft_pwd;
    f[2] = ft_export;
    f[3] = ft_env;
    f[4] = ft_unset;
    f[5] = ft_cd;
    f[6] = ft_exit;
}

/*
** launching its functions
**
** @param *all general structure
** @param *lst command pointer
** @return 1 if the command is executed, 0 if not executed, exitstatus
** (errno number) in case of the error
*/

int			start_cmd(t_all *all, t_cmd *lst)
{
	int			i;
	const char	*name[7] = { "echo", "pwd", "export", "env", "unset", "cd",
				"exit" };
	int			(*f[7])(t_all*, t_cmd*);

	i = 0;
	init_f(f);
	while (i < 7)
	{
		if (!ft_strncmp(lst->name, name[i],
			ft_strlen(name[i]) + 1))
		{
			if (f[i](all, lst) != 0)
				return (all->exit_status);
			return (0);
		}
		i++;
	}
	return (-1);
}

int     execve_with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
	char	*fullname;

	fullname = NULL;
	all->exit_status = 0;
	if (!(envp = deconvert_env(&all->my_env)) ||
		!(argv = convert_argv(cmd)))
		return (free_local(envp, argv, &fullname, -1));
	if (!(fullname = get_full_cmd_name(all, cmd)))
		return (free_local(envp, argv, &fullname, 0));
	if (execve(fullname, argv, envp) == -1)
		exit(ft_error(cmd->name, ": permission denied", 13, all));
	free_local(envp, argv, &fullname, 0);
	exit(0);
}

int     exec_command_pipe(t_all *all, t_cmd *cmd)
{
	pid_t	pid;
	int res_cmd;

	errno = 0;
	pipe(cmd->fd_pipe);
	if ((pid = fork()) == -1)
		return (ft_error(cmd->name, ": failed to fork", 13, all));
	if (pid == 0)
	{
		open_pipe_fd(cmd);
		init_signals(all, 'c');
		if (cmd->prev && cmd->prev->pipe == 1 && (dup2(cmd->prev->fd_pipe[0], 0) < 0))
			exit(all->exit_status);
		if ((res_cmd = start_cmd(all, cmd)) > 0)
			exit(all->exit_status);
		if (res_cmd == -1)
			execve_with_pipe(all, cmd, NULL, NULL);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &all->res, 0);
		close_pipe_fd(cmd);
	}
	all->exit_status = errno;
	init_signals(all, 'p');
	return (all->exit_status);
}

int     with_pipe(t_all *all, t_cmd *cmd)
{
	if (cmd->redir->r[0] != '\0')
	{
		if (init_redirect(all, cmd, 1) != 0)
			return (all->exit_status);
	}
	else
		if (exec_command_pipe(all, cmd) != 0)
			return (all->exit_status);
	return (all->exit_status);
}

int     no_pipe(t_all *all, t_cmd *cmd)
{
	if (cmd->redir->r[0] != '\0')
	{
		if (init_redirect(all, cmd, 0) != 0)
			return (all->exit_status);
	}
	else
	{
		if (exec_command(all, cmd) != 0)
			return (all->exit_status);
	}
	return (all->exit_status);
}
