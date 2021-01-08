/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 18:55:00 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Zeroes all parameters in the structure t_all
**
** @param *all general structure
*/

static void	clear(t_all *all)
{
	all->my_env = NULL;
	all->cmd = NULL;
	all->line = NULL;
	all->pos = 0;
	all->res = 1;
	all->exit_status = 0;
}

/*
** Updates all parameters of the t_all structure to the standard
** ones to get a new line from the user
**
** @param *all general structure
*/

static void	update_main(t_all *all)
{
	clear_cmd(&all->cmd);
	free(all->line);
	all->line = NULL;
	all->pos = 0;
}

/*
** Main function
**
** @param args number of arguments
** @param **argv arguments
** @param **env environment variables
** @return 0 if good, otherwise -1
*/

int			main(int args, char **argv, char **env)
{
	t_all	all;

	(void)args;
	(void)argv;
	clear(&all);
	convert_envp(&(all.my_env), env);
	ft_putstr_fd("bash-3.2$ ", 1);
	while (get_next_line(1, &all.line))
	{
		if (all.line)
		{
			if (parser_string(&all) == -1)
				return (clear_all(&all));
			if (parser_cmd(&all) == -1)
				return (clear_all(&all));
			update_main(&all);
		}
		ft_putstr_fd("bash-3.2$ ", 1);
	}
	return (all.exit_status);
}
