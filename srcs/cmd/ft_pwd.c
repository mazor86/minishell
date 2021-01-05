/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:43:41 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/05 20:52:04 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** executes the pwd command
**
** @param *all general structure
** @param *cmd command structure
** @return 0 if good, otherwise -1
*/

int		ft_pwd(t_all **all)
{
	int i;

	i = 0;
	if((*all)->cmd->argv[0] != 0)
	{
		write(1, "Error. Wrong number of arguments.", 34);
		g_exit_status = 2;
		return (g_exit_status);
	}
	else
	{
		while (ft_strncmp((*all)->my_env[i].name, "PWD", ft_strlen((*all)->my_env[i].name)) != 0)
			i++;
		write(1, (*all)->my_env[i].value, ft_strlen((*all)->my_env[i].value));
		write(1, "\n", 1);
	}
	g_exit_status = 0;
	return (g_exit_status);
}
