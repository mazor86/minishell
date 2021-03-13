/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:21:32 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/13 02:44:51 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Clears the entire array of t_env structures
**
** @param **my_env
*/

void	del_one_env(t_env *my_env)
{
	if (my_env->name)
	{
		free(my_env->name);
		my_env->name = NULL;
	}
	if (my_env->value)
	{
		free(my_env->value);
		my_env->value = NULL;
	}
	my_env->standard = 0;
}

void	free_t_env(t_env **my_env)
{
	t_env	*temp;
	t_env	*save;

	if (my_env)
	{
		temp = *my_env;
		while (temp)
		{
			save = temp->next;
			del_one_env(temp);
			free(temp);
			temp = save;
		}
	}
}
