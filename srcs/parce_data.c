/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:03:38 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/07 14:16:55 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

void	ft_check_name(char **name)
{
	int i;

	i = 0;
	while (*name[i] != '\0')
	{
		if ()
	}

}

/*static void	init_funcs_array(int (**function)(t_list command, char *line))
{
	//function[0] = ft_write_r;
	//function[1] = ft_write_path;
	//function[2] = ft_write_path;
	//function[3] = ft_write_path;
	//function[4] = ft_write_path;
	//function[5] = ft_write_colour;
	//function[6] = ft_write_colour;
}*/

int		parce_line(char ***command, char *line)
{
	int i;
	t_data data;

	i = 0;
	data.name = ft_strcut(line, ' ');
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	ft_check_name(&data.name);
	return (0);
}
