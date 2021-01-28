/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:47:58 by mazor             #+#    #+#             */
/*   Updated: 2021/01/10 12:40:18 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** j - number of element to remove.
*/

static void	ft_rm_element(t_all *all, char *name)
{
	t_env *temp;
	t_env **begin;

	begin = &all->my_env;
	temp = all->my_env;
	while (all->my_env)
	{
		if (ft_strcmp(all->my_env->name, name) == 0)
		{
			temp->next = temp->next->next;
			del_one_env(all->my_env);
		}
		else
			temp = all->my_env;
		all->my_env = all->my_env->next;
	}
	all->my_env = *begin;
}

int			ft_unset(t_all *all, t_cmd *cmd)
{
	int i;

	i = 0;
	all->exit_status = 0;
	if (cmd->argv[0] != NULL)
	{
		while (cmd->argv[i] != NULL)
		{
			ft_rm_element(all, cmd->argv[i]);
			i++;
		}
	}
	return (all->exit_status);
}
