/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:48:09 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/08 15:17:25 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*copy_env(t_env *my_env)
{
	t_env	*copy;
	int		len;
	int		i;

	len = 0;
	while (my_env[len].name != NULL)
		len++;
	i = 0;
	if (!(copy = (t_env*)malloc(sizeof(t_env) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (!(copy[i].name = ft_strdup(my_env[i].name)) ||
		!(copy[i].value = ft_strdup(my_env[i].value)))
			return (NULL);
		copy[i].standard = my_env[i].standard;
		i++;
	}
	copy[i].name = NULL;
	return (copy);
}

int		count_var(t_env *var)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (var[i].name != NULL)
		len++;
	return (len);
}

void	sort_env(t_env *var)
{
	t_env	tmp;
	int		j;
	int		i;
	int		num;

	j = 0;
	num = count_var(var);
	while (j < num)
	{
		i = 0;
		while (i < num - j)
		{
			if (var[i].name[0] < var[i + 1].name[0] && var[i + 1].name != NULL
			&& var[i].name != NULL)
			{
				tmp = var[i];
				var[i] = var[i + 1];
				var[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

int		change_env(t_env *my_env, char *var_name, char *new_value)
{
	int i;

	i = 0;
	while (my_env[i].name != NULL)
	{
		if (ft_strcmp(my_env[i].name, var_name) == 0)
		{
			free(my_env[i].value);
			if (!(my_env[i].value = ft_strdup(new_value)))
				return (ft_error("export", "out of memory", 12, NULL));
			break ;
		}
		i++;
	}
	return (0);
}