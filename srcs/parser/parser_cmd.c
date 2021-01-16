/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/17 04:11:54 by tisabel          ###   ########.fr       */
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

int	start_cmd(t_all *all, t_cmd *lst)
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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** clears strings
**
** @param **split array of strings
** @param **split2 array of strings
** @param **text pointer to string
** @param ret return
** @return ret
*/

static int	free_local(char **split, char **split2, char **text, int ret)
{
	if (split)
		free_array(split);
	if (split2)
		free_array(split2);
	if (*text)
		free(*text);
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

int	start_execve(t_all *all, t_cmd *lst, char **envp, char **argv)
{
	pid_t	pid;
	char	*fullname;

	fullname = NULL;
	if (!(envp = deconvert_env(all)) ||
		!(argv = convert_argv(lst)))
		return (free_local(envp, argv, &fullname, -1));
	if (!(fullname = get_full_cmd_name(all, lst)))
		return (free_local(envp, argv, &fullname, 0));
	if ((pid = fork()) == -1)
		return (ft_error(lst->name, ": failed to fork", 13, all));
	if (pid == 0)
	{
		if (execve(fullname, argv, envp) == -1)
		{
			return (ft_error(lst->name,
				": permission denied", 13, all));
		}
		exit(0);
	}
	else
		waitpid(pid, &all->res, 0);
	return (free_local(envp, argv, &fullname, 0));
}

int			exec_command(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
	int res_cmd;

	if ((res_cmd = start_cmd(all, cmd)) != 0)
		return (all->exit_status);
	if (!res_cmd)
		start_execve(all, cmd, envp, argv);
	return (all->exit_status);
}

/*
** execute the command
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

int			parser_cmd(t_all *all)
{
	t_cmd	*lst;
	char	**envp;
	char	**argv;

	lst = all->cmd;
	envp = NULL;
	argv = NULL;
	if (parser_syntax_errors(all) == 1)
		return (0);
	while (lst)
	{
		if (!is_null_cmd(lst))
		{
			if (lst->pipe == 1)
			{
				if (with_pipe(all, lst, envp, argv) != 0)
					return (all->exit_status);
			}
			else
			{
				if (lst->redir[0] != '\0')
				{
					if (init_redirect(all, lst, envp, argv) != 0)
						return (all->exit_status);
					while (lst->next->redir[0] != '\0')
						lst = lst->next;
				}
				else
				{
					if (exec_command(all, lst, envp, argv) != 0)
					return (all->exit_status);
				}
			}
		}
		lst = lst->next;
	}
	return (0);
}
