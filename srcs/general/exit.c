/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:08 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/08 21:53:44 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_var(t_var **my_env)
{
	int i;

	i = 0;
	while ((*my_env)[i].name != NULL)
	{
		free((*my_env)[i].name);
		(*my_env)[i].name = NULL;
		free((*my_env)[i].value);
		(*my_env)[i].value = NULL;
		i++;
	}
	free((*my_env));
	(*my_env) = NULL;
}

void	free_struct(t_data *data)
{
	free_array(&data->argum);
	if(data->name != NULL)
    {
        free(data->name);
        data->name = NULL;
    }
	if (data->tail != NULL)
    {
        free(data->tail);
        NULL;
    }
    data->pipe = 0;
    data->semicolon = 0;
}

void    wrong_command(t_data *data, t_var **my_env)
{
    free_t_var(my_env);
    free_struct(data);
    ft_putstr_fd("Error\n Wrong command", 2);
    exit (1);
}