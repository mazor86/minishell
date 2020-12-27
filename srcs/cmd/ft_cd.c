/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 14:48:06 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/25 18:26:07 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_local(char **text, char **text1)
{
	if (*text)
		free(*text);
	if (*text1)
		free(*text1);
	return (-1);
}

static int	cd_to_path(t_all *all, char *arg)
{
	char	*pwd_old;
	char	*pwd_new;

	pwd_new = NULL;
	if (!(pwd_old = getcwd(NULL, 0)))
		return (-1);
	if (chdir(arg) != 0)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		all->res = 1;
	}
	else
	{
		if (!(pwd_new = getcwd(NULL, 0)))
			return (free_local(&pwd_old, &pwd_new));
		if (update_env(all, "PWD", pwd_new, 0) == -1 ||
		update_env(all, "OLDPWD", pwd_old, 1) == -1)
			return (free_local(&pwd_old, &pwd_new));
	}
	free_local(&pwd_old, &pwd_new);
	return (0);
}

static int	cd_to(t_all *all, char *name)
{
	t_env	*env;

	if (!(env = get_env(all, name)))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" not set\n", 2);
		all->res = 1;
	}
	else
	{
		if (cd_to_path(all, env->par) == -1)
			return (-1);
	}
	return (0);
}

int			ft_cd(t_all *all, t_cmd *cmd)
{
	all->res = 0;
	if (!ft_strncmp(cmd->argv[0], "", 1))
		return (cd_to(all, "HOME"));
	else
	{
		if (!cmd->argv[1])
		{
			if (!ft_strncmp(cmd->argv[0], "-", 2))
				return (cd_to(all, "OLDPWD"));
			return (cd_to_path(all, cmd->argv[0]));
		}
		else
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			all->res = 1;
		}
	}
	return (0);
}
