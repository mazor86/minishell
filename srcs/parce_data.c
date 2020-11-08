/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:03:38 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/08 20:00:11 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void init_struct(t_data *data)
{
	data->name = NULL;
	data->flag = NULL;
	data->argum = NULL;
	data->tail = NULL;
}

int	ft_parce_s_quotes(char *line, t_data *data, char **my_env)
{
	int i;

	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			data->argum = new_arg(&(data->argum), ft_strcut(line, '\''));
			return (i);
		}
		i++;
	}
	return (i);
}

int		parce_command(t_list **command, char *line, char **my_env)
{
	int i;
	int n;
	t_data data;
	static char str[8] = "=\"\\ $'|;";

	i = 0;
	init_struct(&data);
	while (line[i] != '|')
	{
		while ((n = ft_strfind(str, line[i])) != 0 && line[i] != '\0')
			i++;
		if (line[i] == '=')
			ft_set_var(&data, my_env); // create set_var
		data.name = ft_strcut(line, str[n]);
		if (line[i] == '\'')
			i += ft_parce_s_quotes(&line[i + 1], &data, my_env);
		else if (line[i] == '"')
			i += ft_parce_d_quotes(&line[i + 1], &data, my_env);
	}
	return (i);
}

parce_line(t_list **command, char *line, char **my_env)
{
	int i;

	i = 0;
	while (line [i] != '\0')
	{

	}
}
