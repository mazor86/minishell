/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:45:35 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 19:44:12 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_cd(t_all *all)
{
	int i;
	char *path;

	i = 0;
	path = all->cmd->argv[0] == NULL ? get_var(all->my_env, "HOME") : all->cmd->argv[0];
	if (chdir(path) < 0)
	{
		write (1, "bash: cd: ", 11);
		write (1, path, ft_strlen(path));
		write (1, ": No such file or directory", 28);
		all->exit_status = 1;
		return (1);
	}
	change_env(all, "OLD_PWD", get_var(all->my_env, "PWD"));
	change_env(all, "PWD", getcwd(NULL, _PC_PATH_MAX));
	return (0);
}
