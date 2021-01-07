/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:47:58 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 00:55:15 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_rm_element(t_env **my_env, int j)
{
	t_env *new_env;
	int len;
	int i;

	i = 0;
	len = count_var(*my_env);
	if (!(new_env = (t_env*)malloc(sizeof(t_env) * (len + 1))))
		return (ft_error("unset", "out of memory", 12, NULL));
	while (i < len)
	{
		if (i != j)
		{
			if (!(new_env[i].name = ft_strdup((*my_env)[i].name))
			|| !(new_env[i].value = ft_strdup((*my_env)[i].value)))
				return (ft_error("unset", "out of memory", 12, NULL));
			new_env[i].standard = (*my_env)[i].standard;
		}
		i++;
	}
	new_env[i].name = NULL;
	free_t_env(my_env);
	*my_env = new_env;
	return (0);
}

int		ft_unset(t_all **all)
{
	int i;
	int j; // сделать список элементов которые нужно удалить и удалять все за один проход.

	i = 0;
	g_exit_status = 0;
	if ((*all)->cmd->argv[0] == NULL)
		return (0);
	else
	{
		while ((*all)->cmd->argv[i] != NULL)
		{
			j = 0;
			while ((*all)->my_env[j].name != NULL)
			{
				if (ft_strncmp((*all)->my_env[i].name, (*all)->cmd->argv[j], ft_strlen((*all)->my_env[i].name) + 1) == 0)
				{
					ft_rm_element(&((*all)->my_env), j);
					break ;
				}
				j++;
			}
			i++;
		}
	}
	return (g_exit_status);
}
