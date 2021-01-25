/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:48:09 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/17 04:14:46 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** creates an enviroment variables structure
**
** @return env pointer, otherwise NULL
*/

t_env	*init_env(void)
{
	t_env	*my_env;

	if (!(my_env = malloc(sizeof(t_env))))
		return (NULL);
	if (!(my_env->name = ft_strdup(""))
		|| !(my_env->value = ft_strdup("")))
		return (NULL);
	my_env->standard = 0;
	my_env->next = NULL;
	return (my_env);
}

t_env	*copy_env(t_env *my_env)
{
	t_env	*copy;
	t_env	*temp;
	t_env	*begin;

	temp = my_env;
	if (!(copy = (t_env*)malloc(sizeof(t_env))) ||
		!(copy->name = ft_strdup(temp->name))
		|| !(copy->value = ft_strdup(temp->value)))
		return (NULL);
	copy->standard = temp->standard;
	begin = copy;
	while (temp)
	{
		if (temp->next != NULL)
		{
			if (!(copy->next = (t_env*)malloc(sizeof(t_env))) ||
				!(copy->next->name = ft_strdup(temp->next->name)) ||
				!(copy->next->value = ft_strdup(temp->next->value)))
				return (NULL); // почистить копию листа
			copy->next->standard = temp->next->standard;
			copy = copy->next;
		}
		temp = temp->next;
	}
	copy->next = NULL;
	return (begin);
}

int		count_env(t_env *my_env)
{
	int	len;

	len = 0;
	while (my_env)
	{
		len++;
		my_env = my_env->next;
	}
	return (len);
}

void swap_envs(t_env **begin, t_env *my_env)
{
    t_env *temp;

    temp = *begin;
    if (*begin != my_env)
    {
        while (temp->next != my_env)
            temp = temp->next;
        temp->next = my_env->next;
        my_env->next = my_env->next->next;
        temp->next->next = my_env;
    }
    else
    {
        *begin = temp->next;
        temp->next = temp->next->next;
        (*begin)->next = temp;
    }
}
void	sort_env(t_env **my_env)
{
	t_env	*temp;
	int		len;
	int		i;

	i = 0;
	len = count_env(*my_env);
	while (i < len - 1)
	{
        temp = *my_env;
		while (temp->next)
		{
			if (ft_strcmp(temp->name, temp->next->name) > 0)
			{
				swap_envs(my_env, temp);
			}
			else
                temp = temp->next;
		}
		i++;
	}
}

int		change_env(t_all *all, char *var_name, char *new_value)
{
	t_env *temp;

	temp = all->my_env;
	while (temp)
	{
		if (ft_strcmp(temp->name, var_name) == 0)
		{
			free(temp->value);
			if (!(temp->value = ft_strdup(new_value)))
				return (ft_error("export", "out of memory", 12, all));
			break ;
		}
		temp = temp->next;
	}
	return (0);
}
