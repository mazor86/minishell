/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:18:48 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/26 11:30:53 by tisabel          ###   ########.fr       */
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

int		no_pipe(t_all *all, t_cmd *cmd)
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