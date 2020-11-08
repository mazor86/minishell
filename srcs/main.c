/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/11/08 20:45:33 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int args, char **argv, char **env)
{
	t_data	all;
	char	*line;
	t_list	*command;
	char	**my_env;
	
	(void)args;
	(void)argv;
	line = NULL;
	my_env = ft_copy_array(env); // write
	while (get_next_line(0, &line) > 0)
	{
		printf("%s\n", line);
		parce_line(&command, line, &my_env);
		ft_check_name(&command, &my_env);
		free(line);
		line = NULL;
	}
	return (0);
}
