/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:14:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 17:14:50 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **copy_array(char **array)
{
    unsigned int	i;
	unsigned int	j;
	char			**new_array;

	i = 0;
	j = 0;
    while (array[j] != NULL)
        j++;
	if (!array || !(new_array = (char**)malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	while (array[i] != NULL)
	{
		new_array[i] = ft_strdup(array[i]);
		if (new_array[i] == NULL)
            free_array(&new_array);
			i++;
	}
	new_array[i] = NULL;
	return (new_array);
}