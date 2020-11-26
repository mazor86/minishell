/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:00:28 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 13:30:13 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The function frees all elements of an array and then
** sets the pointer to NULL.
*/

void    free_array(char ***array)
{
    int	i;

	i = 0;
	if (*array != NULL)
    {
        while ((*array)[i] != NULL)
        {
            free((*array)[i]);
            (*array)[i] = NULL;
            i++;
        }
        *array = NULL;
    }
}

/*
** The function adds an element to the array, realocating the memory and 
** retutns a number of elements in the array, in case of error returns (-1).
*/

int     new_arg(char ***array, char *new_arg)
{
    int i;
    int     num;
    char    **new_array;

    num = 0;
    i = 0;
    if (!array)
        return (-1);
    if (*array == NULL)
        num = 0;
    else
    {
        while ((*array)[num] != NULL)
            num++;
        num++;
    }
    if (!(new_array = (char**)malloc(sizeof(char*) * (num + 1))))
        return (-1);
    while (i < num)
    {
        new_array[i] = ft_strdup((*array)[i]);
        i++;
    }
    new_array[i++] = ft_strdup(new_arg);
    new_array[i] = NULL;
    free_array(array);
    return (num + 2);
}