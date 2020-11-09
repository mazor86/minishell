/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:08 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 20:03:12 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_struct(t_data *data)
{
	free_array(&data->argum);
    free(data->name);
    free(data->tail);
    data->pipe = 0;
    data->semicolon = 0;
}

void    wrong_command(t_list **command, char ***my_env)
{
    free_array(my_env);
    free_struct((*command)->content);
    ft_putstr_fd("Error\n Wrong command", 2);
    exit (1);
}