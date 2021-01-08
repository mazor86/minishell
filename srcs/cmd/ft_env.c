/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:48:51 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 19:01:43 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** executes the env command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int		ft_env(t_all *all)
{
	int i;

	i = 0;
	if(all->cmd->argv[0] != 0)
		{
			write(1, "Error. Wrong number of arguments.", 34);
			all->exit_status = 2;
			exit(all->exit_status);
		}
	else
		while (all->my_env[i].name != NULL)
		{
			if (all->my_env[i].standard == 1)
			{
				write(1, all->my_env[i].name, ft_strlen(all->my_env[i].name));
				write(1, "=", 1);
				write(1, all->my_env[i].value, ft_strlen(all->my_env[i].value));
				write(1, "\n", 1);
			}
		i++;
		}
	return (0);
}
