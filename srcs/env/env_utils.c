/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:48:09 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/11 13:09:50 by tisabel          ###   ########.fr       */
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
	
	if (!(my_env->name = ft_strdup("")) || !(my_env->value = ft_strdup("")))
		return (NULL);
	my_env->standard = 0;
	my_env->next = NULL;
	return (my_env);
}

t_env	*copy_env(t_env *my_env)
{
	t_env	*copy;
	t_env	**begin;

	copy = init_env();
	begin = &copy;
	while (my_env)
	{
		if (!(copy->name = ft_strdup(my_env->name)) ||
		!(copy->value = ft_strdup(my_env->value)))
			return (NULL);
		copy->standard = my_env->standard;
		my_env = my_env->next;
		copy = copy->next;
	}
	copy->next = NULL;
	return (*begin);
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

void	sort_env(t_env **my_env)
{
	t_env	**begin;
	t_env	*tmp_1;
	t_env	*tmp_2;
	int		len;
	int		i;

	i = 0;
	begin = my_env;
	len = count_env(*my_env);
	while (i < len - 1)
	{
		while ((*my_env)->next)
		{
			if ((*my_env)->name < (*my_env)->next->name)
			{
				tmp_1 = *my_env;
				tmp_2 = (*my_env)->next->next;
				*my_env = (*my_env)->next;
				(*my_env)->next = tmp_1;
				tmp_1->next = tmp_2;
			}
			*my_env = (*my_env)->next;
		}
		*my_env = *begin;
		i++;
	}
}

int		change_env(t_all *all, char *var_name, char *new_value)
{
	t_env **temp;

	temp = NULL;
	*temp = all->my_env;
	while (all->my_env->name != NULL)
	{
		if (ft_strcmp(all->my_env->name, var_name) == 0)
		{
			free(all->my_env->value);
			if (!(all->my_env->value = ft_strdup(new_value)))
				return (ft_error("export", "out of memory", 12, all));
			break ;
		}
		all->my_env = all->my_env->next;
	}
	all->my_env = *temp;
	return (0);
}