/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:45:35 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/02 13:34:26 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** clears all lines
**
** @param **text pointer to array of strings
** @param **text1 pointer to array of strings
** @return -1
*/

static int	free_local(char **text, char **text1)
{
	if (*text)
		free(*text);
	if (*text1)
		free(*text1);
	return (-1);
}

/*
** goes to directory and updates environment variables
**
** @param *all general structure
** @param *arg environment variable value
** @return 0 if good, otherwise -1
*/

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

/*
** makes a check that there is an environment variable name, if there is,
** go ahead, otherwise we display an error
**
** @param *all general structure
** @param *name environment variable name
** @return 0 if good, otherwise -1
*/

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

/*
** executes the cd command
**
** @param *all general structure
** @param *cmd command structure
** @return 0 if good, otherwise -1
*/

int			ft_cd(t_all **all)
{
	int i;
	int n;
	char *path;

	i = 0;
	path = (*all)->cmd->argv[0] == NULL ? get_home((*all)->cmd) : (*all)->cmd->argv[0];
	if (chdir(path) < 0)
	{
		write (1, "error", 5);
		exit (2); // set error path not found or other
	}
	change_var("OLD_PWD", get_var((*all)->my_env, "PWD"));
	change_var("PWD", getcwd(NULL, _PC_PATH_MAX));
	return (0);
}
