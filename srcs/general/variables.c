/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:07 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/01 16:36:07 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var(char *line, t_var **my_env)
{
	int		i;
	int		j;
	t_var	*temp;
	int		len_envp;

	i = 0;
	j = 0;
	temp = *my_env;
	while ((*my_env)[len_envp].name != NULL)
		len_envp++;
	if (!(*my_env = (t_var*)malloc(sizeof(t_var) * (len_envp + 2))))
		exit (1);
	while (temp[i].name != NULL)
	{
		(*my_env)[i].name = ft_strdup(temp[i].name);
		(*my_env)[i].value = ft_strdup(temp[i].value);
		(*my_env)[i].standard = temp[i].standard;
		i++;
	}
	free_t_var(&temp);
	(*my_env)[i].name = ft_strcut(line, '=');
	while (line[j] != '=')
		j++;
	(*my_env)[i].value = ft_strdup(&line[j + 1]);
	(*my_env)[i].standard = 0;
	(*my_env)[i + 1].name = NULL;
}

int	get_var(t_var **my_env, char *var_name)
{
	int i;

	i = 0;
	while (ft_strcmp((*my_env)[i].name,var_name) != 0 && (*my_env)[i].name != NULL)
		i++;
	return ((*my_env)[i].name == NULL ? NULL : (*my_env)[i].value);
}