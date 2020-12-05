/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:07 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/06 00:01:40 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_var(char *line, t_var **my_env)
{
	int		i;
	int		j;
	t_var	*temp;
	int		len_envp;

	i = 0;
	temp = *my_env;
	while ((*my_env)[len_envp].name != NULL)
		len_envp++;
	if (!(*my_env = (t_var*)malloc(sizeof(t_var) * (len_envp + 2))))
		exit (1);
	while (temp[i].name != NULL)
	{
		(*my_env)[i].name = ft_strdup(temp[i].name);
		free(temp[i].name);
		temp[i].name = NULL;
		(*my_env)[i].value = ft_strdup(temp[i].value);
		free(temp[i].value);
		temp[i].value = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
	(*my_env)[i].name = ft_strcut(line, '=');
	while (line[j] != '=')
		j++;
	(*my_env)[i].value = ft_strdup(&line[j + 1]);
	i++;
	(*my_env)[i].name = NULL;
	return (0);
}

int	get_var(char *line, t_data *data, t_var **my_env)
{
	(void)data;
	(void)my_env;
	(void)line;
	return (0);
}