/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:07 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/17 04:02:22 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var(t_env *my_env, char *var_name)
{
	while (ft_strncmp(my_env->name, var_name, ft_strlen(my_env->name) + 1) != 0
		&& my_env->next != NULL)
		my_env = my_env->next;
	return (my_env->name == NULL ? NULL : my_env->value);
}
