/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:08:42 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/05 22:23:59 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The function checks if there are only digits in the string;
*/

int     check_digit(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if(ft_isdigit(str[i]) != 1)
            return (0);
        i++;
    }
    return (1);
}