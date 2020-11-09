/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:08 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 18:32:15 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    wrong_command(t_list **command, char ***my_env)
{
    free_array(my_env);
    free_array(&((*command)->content->argum));
    free((*command)->content->name);
    free((*command)->content->flag);
    free((*command)->content->tail);
    ft_putstr_fd("Error\n Wrong command", 2);
    exit (1);
}