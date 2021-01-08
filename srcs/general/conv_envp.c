/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:21:32 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/08 00:47:05 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_envp(t_env **envp_var, char **envp)
{
	int i;
	int j;
	int len_envp;

	i = 0;
	len_envp = 0;
	while (envp[len_envp])
		len_envp++;
	if (!(*envp_var = (t_env*)malloc(sizeof(t_env) * (len_envp + 1))))
		exit (1);
	while (envp[i] != NULL)
	{
		j = 0;
		(*envp_var)[i].name = ft_strcut(envp[i], '=');
		while (envp[i][j] != '=')
			j++;
		(*envp_var)[i].value = ft_strdup(&envp[i][j + 1]);
		(*envp_var)[i].standard = 1;
		i++;
	}
	(*envp_var)[i].name = NULL;
}