/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:43:41 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/17 03:49:05 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** executes the pwd command
**
** @param *all general structure
** @param *cmd command structure
** @return 0 if good, otherwise exitstatus of the program (errno number)
*/

int		ft_pwd(t_all *all, t_cmd *cmd)
{
	char	*pwd;

	all->exit_status = 0;
	if (ft_strcmp(cmd->argv[0], "") != 0)
		ft_error("pwd", "wrong number of arguments", 21, all);
	if ((pwd = get_var(all->my_env, "PWD")) == NULL &&
	!(pwd = getcwd(NULL, _PC_PATH_MAX)))
		ft_error("pwd", "out of memory", 12, all); // access denied is also possible
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	return (all->exit_status);
}
