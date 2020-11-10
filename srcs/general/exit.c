/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:08 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 21:30:31 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_data *data)
{
	free_array(&data->argum);
    free(data->name);
    free(data->tail);
    data->pipe = 0;
    data->semicolon = 0;
}

void    wrong_command(t_data *data, char ***my_env)
{
    free_array(my_env);
    free_struct(data);
    ft_putstr_fd("Error\n Wrong command", 2);
    exit (1);
}