/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:07 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/08 21:56:51 by tisabel          ###   ########.fr       */
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
		i++;
	}
	free_t_var(&temp);
	(*my_env)[i].name = ft_strcut(line, '=');
	while (line[j] != '=')
		j++;
	(*my_env)[i].value = ft_strdup(&line[j + 1]);
	(*my_env)[i + 1].name = NULL;
}

int	get_var(char *line, t_data *data, t_var **my_env)
{
	(void)data;
	(void)my_env;
	(void)line;
	return (0);
}