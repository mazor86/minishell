/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:13:58 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 21:14:34 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parce_s_quotes(char *line, t_data *data, char ***my_env)
{
	int i;
	//char *arg;

	i = 1;
	if (!my_env)
		return (0);
	while (line[i] != '\0')
	{
		/*if (line[i] == '.')
		{
			if (line[i + 1] == '.')
			{
				
			}
			else
				ft_get_path_dot()
		}*/

		if (line[i] == '\'')
		{
			new_arg(&(data->argum), ft_strcut(line, '\''));
			return (i);
		}
		i++;
	}
	return (i);
}

int		parce_d_quotes(char *line, t_data *data, char ***my_env)
{
	int i;

	i = 1;
	if (!my_env)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '$' || line[i] == '\\')
		{
			
		}
		if (line[i] == '"')
		{
			new_arg(&(data->argum), ft_strcut(line, '\''));
			return (i);
		}
		i++;
	}
	return (i);
}