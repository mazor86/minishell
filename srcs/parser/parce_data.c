/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:03:38 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 19:56:37 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void init_struct(t_data *data)
{
	data->name = NULL;
	data->argum = NULL;
	data->tail = NULL;
	data->pipe = 0;
	data->semicolon = 0;
}

int	set_var(char *line, t_data *data, char ***my_env)
{
	(void)data;
	(void)my_env;
	return (0);
}

int	get_var(char *line, t_data *data, char ***my_env)
{
	(void)data;
	(void)my_env;
	return (0);
}

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

int		parce_command(t_list **command, char *line, char ***my_env)
{
	int i;
	int n;
	int j;
	t_data data;
	static char str[9] = "=\"\\ $'|;";

	i = 0;
	j = 0;
	init_struct(&data);
	while (line[i] != '|' && line[i] != '\0')
	{
		while ((n = ft_strfind(str, line[i])) != 0 && line[i] != '\0')
			i++;
		if (line[i] == '=')
			i += set_var(&line[i + 1], &data, my_env); // create set_var
		else if (line[i] == ' ')
		{
			if (data.name == NULL)
				data.name = ft_strcut(line, str[n]);
			else
				data.argum = new_arg((&data)->argum, ft_strcut(&line[i], ' '));
			while (line[i] == ' ')
				i++;
		}
		else if (line[i] == '\'')
			i += parce_s_quotes(&line[i + 1], &data, my_env);
		else if (line[i] == '"')
			i += parce_d_quotes(&line[i + 1], &data, my_env);
		else if (line[i] == '$')
			i += get_var(&line[i + 1], &data, my_env); // create get_var
		else if (line[i] == '\\')
			i += get_ecran(&line[i + 1], &data, my_env);
		else if (line[i] == '|')
		{
			data.pipe = 1;
			data.argum = new_arg((&data)->argum, ft_strcut(&line[i], '|'));
			exec_pipe(&data, my_env);
			i++;
		}
		else if (line[i] == ';')
		{
			data.semicolon = 1;
			data.argum = new_arg((&data)->argum, ft_strcut(&line[i], ';'));
			exec_semicolon(&data, my_env);
			free_struct(&data);
			i++;
		}
	}
	(*command) = ft_lstnew(&data);
	return (i);
}

/*void	parce_line(t_list **command, char *line, char **my_env)
{
	int i;

	i = 0;
	//while (line [i] != '\0')
	//{
	//}
}*/
