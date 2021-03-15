/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:47:58 by mazor             #+#    #+#             */
/*   Updated: 2021/03/13 02:44:51 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unlink_envs(t_env **begin, t_env *my_env)
{
	t_env *temp;

	temp = *begin;
	if (*begin != my_env)
	{
		while (temp->next != my_env)
			temp = temp->next;
		temp->next = my_env->next;
	}
	else
		*begin = temp->next;
}

static void	ft_rm_element(t_all *all, char *name)
{
	t_env *temp;
	t_env *del;

	temp = all->my_env;
	while (temp)
	{
		del = temp;
		temp = temp->next;
		if (ft_strcmp(del->name, name) == 0)
		{
			unlink_envs(&all->my_env, del);
			del_one_env(del);
			break ;
		}
	}
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
