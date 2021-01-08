/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 19:41:35 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** function pointers initialization
**
** @param **f a pointer to an array of functions
*/

static void	init_f(int (**f)(t_all*))
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

static int	start_cmd(t_all *all, t_cmd *lst)
{
	int			i;
	const char	*name[7] = { "echo", "pwd", "export", "env", "unset", "cd",
				"exit" };
	int			(*f[7])(t_all*);

	i = 0;
	init_f(f);
	while (i < 7)
	{
		if (!ft_strncmp(lst->name, name[i],
			ft_strlen(name[i]) + 1))
		{
			if (f[i](all) != 0)
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

static int	start_execve(t_all *all, t_cmd *lst, char **envp, char **argv)
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

/*
** execute the command
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

int			parser_cmd(t_all *all)
{
	t_cmd	*lst;
	int		res_cmd;
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
			if ((res_cmd = start_cmd(all, lst)) == -1)
				return (-1);
			if (!res_cmd)
			{
				if (start_execve(all, lst, envp, argv) == -1)
					return (-1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
