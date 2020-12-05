/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:08 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/05 23:37:35 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    free_array(my_env);
    free_struct(data);
    ft_putstr_fd("Error\n Wrong command", 2);
    exit (1);
}