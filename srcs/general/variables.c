/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:07 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/12 23:53:30 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var(t_env *my_env, char *var_name)
{
	int 	flag;

	while ((flag = ft_strncmp(my_env->name, var_name, ft_strlen(my_env->name) + 1)) != 0
		&& my_env->next != NULL)
	{
		my_env = my_env->next;
	}
	return (flag != 0 ? ft_strdup("") : my_env->value);
}
