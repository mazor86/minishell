/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:03:38 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/08 20:02:03 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_parce_funcs_array(int (**function)(char *line, t_data *data,
		t_var **my_env))
{
	function[0] = set_var;
	function[1] = parce_d_quotes;
	function[2] = get_ecran;
	function[3] = get_arg;
	function[4] = get_var;
	function[5] = parce_s_quotes;
	function[6] = exec_pipe;
	function[7] = exec_semicolon;
}

int	get_ecran(char *line, t_data *data, t_var **my_env)
{
	(void)data;
	(void)my_env;
	(void)line;
	return (0);
}

int	get_arg(char *line, t_data *data, t_var **my_env)
{
	int i;

	i = 0;
	if (!my_env)
		return (0);
	while (line[i] != ' ' && line[i] != '\0')
	    i++;
	if (data->name == NULL)
		data->name = ft_strcut(line, ' ');
	else
		new_arg(&(data->argum), ft_strcut(line, ' '));
	return (i);
}

int		parce_command(t_data *data, char *line, t_var **my_env)
{
	int			i;
	int			n;
	int			j;
	static char str[8] = "=\"\\ $'|;";
	int			(*f[8])(char *line, t_data *data, t_var **my_env);

	i = 0;
	j = 0;
	init_parce_funcs_array(f);
	while (line[i] != '|' && line[i] != '\0')
	{
		while ((n = ft_strfind(str, line[i])) == 0 && line[i] != '\0')
			i++;
		if (ft_strfind(str, line[i]) != 0)
        {
            j += f[n - 1](&line[j], data, my_env) + 1; // create set_var
            i = j;
        }
		else
        {
            j += f[3](&line[j], data, my_env) + 1;
            i = j;
        }
	}
	return (i);
}
