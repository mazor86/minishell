/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:14:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 13:31:23 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **copy_array(char **env_orig)
{
    unsigned int	i;
	unsigned int	j;
	char			**my_env;

	i = 0;
	j = 0;
    while (env_orig[j] != NULL)
        j++;
	if (!env_orig || !(my_env = (char**)malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	while (env_orig[i] != NULL)
	{
		my_env[i] = ft_strdup(env_orig[i]);
		if (my_env[i] == NULL)
            free_array(&my_env);
	}
	my_env[i] = NULL;
	return (my_env);
}