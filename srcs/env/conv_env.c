/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:21:32 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/12 23:53:30 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		convert_env(t_env **env_var, char **env, t_all *all)
{
	int		i;
	int		n;
	t_env	*temp;

	i = 0;
	if (!(temp = init_env()))
		return (ft_error("unset", "out of memory", 12, all));
	*env_var = temp;
	while (env[i] != NULL)
	{
		temp->name = ft_strcut(env[i], '=');
		n = ft_strfind(env[i], '=');
		temp->value = ft_strdup(&env[i][n]);
		temp->standard = 1;
		if (env[i + 1] == NULL)
			temp->next = NULL;
		else
		{
			if (!(temp->next = init_env()))
				return (ft_error(NULL, "out of memory", 12, all));
			temp = temp->next;
		}
		i++;
	}
	return (0);
}
