/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:45:35 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 20:15:57 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_cd(t_all *all, t_cmd *cmd)
{
	char *path;

	all->exit_status = 0;
	path = cmd->argv[0] == NULL ? get_var(all->my_env, "HOME") : cmd->argv[0];
	if (chdir(path) < 0)
	{
		ft_error("cd", "No such file or directory", 2, all);
		return (all->exit_status);
	}
	if (get_var(all->my_env, "OLD_PWD") == NULL)
		add_arg(all, "OLD_PWD", &all->my_env);
	change_env(all, "OLD_PWD", get_var(all->my_env, "PWD"));
	change_env(all, "PWD", getcwd(NULL, _PC_PATH_MAX));
	return (all->exit_status);
}
