/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:00:08 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/08 19:31:23 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_wrong_command(t_list **command, char **my_env)
{
    ft_putstr_fd("Error\n Wrong command", 2);
    exit (1);
}