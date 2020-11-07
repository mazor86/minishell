/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:03:38 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/07 18:18:26 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		parce_line(t_list **command, char *line)
{
	int i;
	int n;
	t_data data;
	static char str[6] = "=\"\\ $'";

	i = 0;
	while ((n = ft_strfind(str, line[i])) != 0 && line[i] != '\0')
		i++;
	data.name = ft_strcut(line, str[n]);
	ft_check_name(command);
	return (0);
}
