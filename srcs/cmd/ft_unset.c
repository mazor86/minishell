/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:47:58 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/05 20:54:49 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_rm_element(t_env **my_env, int j)
{
	t_env *new_env;
	int len;
	int i;

	i = 0;
	len = 0;
	while ((*my_env)[len].name != NULL)
		len++;
	if (!(new_env = (t_env*)malloc(sizeof(t_env) * (len + 1))))
			exit (2);
	while (i < len)
		if (i != j)
		{
			new_env[i].name = ft_strdup((*my_env)[i].name);
			new_env[i].value = ft_strdup((*my_env)[i].value);
			new_env[i].standard = (*my_env)[i].standard;
			i++;
		}
	new_env[i].name = NULL;
	free_t_var(my_env);
	*my_env = new_env;
}

int		ft_unset(t_all **all)
{
	int i;
	int j; // сделать список элементов которые нужно удалить и удалять все за один проход.

	i = 0;
	if ((*all)->cmd->argv[0] == NULL)
		return (0);
	else
	{
		while ((*all)->cmd->argv[i] != NULL)
		{
			j = 0;
			while ((*all)->my_env[j].name != NULL)
			{
				if (ft_strcmp((*all)->my_env[i].name, (*all)->cmd->argv[j]) == 0)
				{
					ft_rm_element((*all)->my_env, j);
					break ;
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}
