/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:46:57 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/10 18:34:29 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Функиця экспорт выводит переменные которым не быбло присвоено значение,
//а функция env нет. Но через export они присваиваются

#include "minishell.h"

t_var	*copy_env(t_var *my_env)
{
	t_var	*copy;
	int		len;
	int		i;

	len = 0;
	while (my_env[len].name != NULL)
		len++;
	i = 0;
	if (!(copy = (t_var*)malloc(sizeof(t_var) * (len + 1))))
			exit (2);
	
}

void	sort_env(t_var *var)
{
	char	*temp;
	int		j;
	int		i;
	int		num;

	j = 0;
	num = 0;
	while (j < num)
	{
		i = 0;
		while (i < num - j)
		{
			if (var[i].name[0] < var[i + 1].name[0] && var[i + 1].name != NULL
			&& var[i].name != NULL)
			{
				temp = var[i + 1].name;
				var[i + 1].name = var[i].name;
				var[i].name = temp;
			}
			i++;
		}
		j++;
	}
}

int		ft_export(t_data *data, t_var **my_env)
{
	int i;
	t_var *sorted_env;
	int len;

	i = 0;
	if(data->argum[0] != NULL)
	{
		sorted_env = copy_env(*my_env);
		sort_env(&sorted_env);
		while ((*my_env)[i].name != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, (*my_env)[i].name, ft_strlen((*my_env)[i].name));
			write(1, "=", 1);
			write(1, (*my_env)[i].value, ft_strlen((*my_env)[i].value));
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		while (data->argum[i] != NULL)
		{
			check_arg()
		}
	}
	return (0);
	return (0);
}
