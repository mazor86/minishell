/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/11/09 18:41:54 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int args, char **argv, char **envp)
{
	char	*line;
	t_list	*command;
	
	(void)args;
	(void)argv;
	line = NULL;
	ft_putstr_fd("bash-3.2$", 0);
	while (get_next_line(0, &line) > 0)
	{
		ft_putstr_fd("bash-3.2$", 0);
		parce_command(&command, line, &envp);
		check_name(&command, &envp);
		free(line);
		line = NULL;
	}
	return (0);
}
