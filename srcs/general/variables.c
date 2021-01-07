/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:07 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/08 00:46:12 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		set_var(char *line, t_env **my_env)
{
	int		i;
	int		j;
	t_env	*temp;
	int		len_env;

	i = 0;
	j = 0;
	temp = *my_env;
	len_env = count_var(temp);
	if (!(*my_env = (t_env*)malloc(sizeof(t_env) * (len_env + 2))))
		return( ft_error(NULL, "out of memory", 12, NULL));
	while (temp[i].name != NULL)
	{
		if (!((*my_env)[i].name = ft_strdup(temp[i].name))
		|| !((*my_env)[i].value = ft_strdup(temp[i].value)))
			return( ft_error(NULL, "out of memory", 12, NULL));
		(*my_env)[i].standard = temp[i].standard;
		i++;
	}
	free_t_env(&temp);
	if (!((*my_env)[i].name = ft_strcut(line, '=')))
		return( ft_error(NULL, "out of memory", 12, NULL));
	while (line[j] != '=')
		j++;
	if (!((*my_env)[i].value = ft_strdup(&line[j + 1])))
		return( ft_error(NULL, "out of memory", 12, NULL));
	(*my_env)[i].standard = 0;
	(*my_env)[i + 1].name = NULL;
	return (g_exit_status = 0);
}

char	*get_var(t_env *my_env, char *var_name)
{
	int i;

	i = 0;
	while (ft_strncmp(my_env[i].name, var_name, ft_strlen(my_env[i].name) + 1) != 0 && my_env[i].name != NULL)
		i++;
	return (my_env[i].name == NULL ? NULL : my_env[i].value);
}