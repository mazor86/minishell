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

//TODO 26 lines in start_execve
int			start_execve(t_all *all, t_cmd *lst)
{
	pid_t		pid;
	char		*fullname;
	extern int	errno;
	char		**envp;
	char		**argv;

	all->exit_status = 0;
	envp = deconvert_env(&all->my_env);
	argv = convert_argv(lst);
	fullname = get_full_cmd_name(all, lst);
	if (envp && argv && fullname)
	{
		if ((pid = fork()) == -1)
			return (ft_error(lst->name, "failed to fork", 13, all));
		if (pid == 0)
		{
			init_signals(all, 'c');
			errno = 0;
			if (execve(fullname, argv, envp) == -1)
				ft_error(lst->name, strerror(errno), errno, all);
			exit(all->exit_status);
		}
		else
			parent_process(pid, all, lst);
		init_signals(all, 'p');
	}
	return (free_local(envp, argv, &fullname, all->exit_status));
}

int			exec_command(t_all *all, t_cmd *cmd)
{
	int res_cmd;

	if (cmd->prev && cmd->prev->pipe == 1)
	{
		if (dup2_closer(cmd->prev->fd_pipe[0], 0) != 0)
			return (all->exit_status);
		if (cmd->redir->r[0] == '\0')
			restore_fds(all);
	}
	if ((res_cmd = start_cmd(all, cmd)) > 0)
		return (all->exit_status);
	if (res_cmd == -1)
		start_execve(all, cmd);
	if (cmd->prev && cmd->prev->pipe != 0)
		restore_fds(all);
	return (all->exit_status);
}

/*
** execute the command
**
** @param *all general structure
** @return 0 if good, otherwise returns exit status and prints error
*/

int			execute_cmd(t_all *all)
{
	t_cmd	*lst;
	int 	redin;
	int 	redout;
	int		i;
	pid_t	pid;
	int 	fd;
	int		ret;

	lst = all->cmd;
	i = 0;
	redin = -1;
	redout = -1;
	while (lst)
	{
		if (!is_null_cmd(lst) || lst->redir->r[0] != '\0')
		{
			save_fds(all);
			if (lst->redir->r[0] != '\0')
			{
				while (lst->redir->r[0] != '\0')
				{
					if (lst->redir[i].r[0] == '<')
					{
						fd = open_file(lst->redir[i].r, lst->redir[i].file);
						close_dup_fd(redin, redout, 0);
						if (fd < 0)
						{
							restore_fds(all);
							return (ft_error(lst->redir[i].file, strerror(2), 2, all));
						}
						redin = fd;
					}
					i++;
				}
				if (redin < 0)
					redin = dup(all->save_fd[0]);
			}
			while (lst)
			{
				if (lst->pipe != 0)
				{
						dup2_closer(redin, 0);
						pipe(lst->fd_pipe);
						redout = lst->fd_pipe[1];
						redin = lst->fd_pipe[0];
				}
				else if (lst->pipe == 0)
				{
					i = 0;
					while (lst->redir->r[0] != '\0')
					{
						if (lst->redir[i].r[0] == '>')
						{
							fd = open_file(lst->redir[i].r, lst->redir[i].file);
							close_dup_fd(redin, redout, 1);
							if (fd < 0)
							{
								restore_fds(all);
								return (ft_error(lst->redir[i].file, strerror(2), 2, all));
							}
							redout = fd;
						}
						i++;
					}
					if (redout < 0)
						redout = dup(all->save_fd[1]);
				}
				dup2_closer(redout, 1);
				if (lst->pipe == 0 && !(lst->prev && lst->prev->pipe == 1))
					ret = execute_cmd(all);
				if (ret > 0)
					return (ft_error(lst->redir[i].file, strerror(2), 2, all));
				if (lst->pipe == 1 || (lst->prev && lst->prev->pipe == 1) || ret == -1)
				{
					if ((pid = fork()) == -1)
						return (ft_error(lst->name, "failed to fork", 13, all));
					if (pid == 0) {
						init_signals(all, 'c');
						if (lst->pipe == 1 || (lst->prev && lst->prev->pipe == 1))
							run_command_pipe(all, lst);
						else
							exec_command(all, lst);
					}
				}
				lst = lst->next;
			}
		}
		mute_signals();
		waitpid(pid, &all->res, 0);
		while (lst->prev->pipe)
		{
			close(lst->fd_pipe[1]);
			close(lst->fd_pipe[0]);
		}
		all->exit_status = errno;
		init_signals(all, 'p');
		lst = lst->next;
	}
	restore_fds(all);
	return (all->exit_status);
}



//void Command::execute()
//{
//save in/out
//	int tmpin=dup(0);
//	int tmpout=dup(1);
//
//set the initial input
//	int fdin;
//	if (infile)
//	{
//		fdin = open(infile,O_READ);
//	}
//	else
//	{
//	// Use default input
//		fdin=dup(tmpin);
//	}
//
//	int ret;
//	int fdout;
//	for(i=0;i<numsimplecommands; i++)
//	{
//		//redirect input
//		dup2(fdin, 0);
//		close(fdin);
//		//setup output
//		if (i == numsimplecommands - 1)
//		{
//		// Last simple command
//			if(outfile)
//			{
//				fdout=open(outfile,â€¦â€¦);
//			}
//			else
//			{
//				// Use default output
//				fdout=dup(tmpout);
//			}
//		}
//		else
//		{
//		// Not last
//		//simple command
//		//create pipe
//			int fdpipe[2];
//			pipe(fdpipe);
//			fdout = fdpipe[1];
//			fdin = fdpipe[0];
//		}// if/else
//		// Redirect output
//		dup2(fdout, 1);
//		close(fdout);
//		// Create child process
//		ret=fork();
//		if(ret==0)
//		{
//			execvp(scmd[i].args[0], scmd[i].args);
//			perror(â€œexecvpâ€);
//			_exit(1);
//		}
//	} //  for
//
//	//restore in/out defaults
//	dup2(tmpin,0);
//	dup2(tmpout,1);
//	close(tmpin);
//	close(tmpout);
//
//	if (!background)
//	{
//	// Wait for last command
//		waitpid(ret, NULL);
//	}
//} // execute