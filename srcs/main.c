/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/10 12:44:52 by tisabel          ###   ########.fr       */
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
	all->save_fd[0] = -1;
	all->save_fd[1] = -1;
	all->pipe_fd[0] = -1;
	all->pipe_fd[1] = -1;
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
	convert_env(&all.my_env, env, &all);
	ft_putstr_fd("bash-3.2$ ", 1);
	init_signals(&all, 'p');
	while (get_next_line(0, &all.line, &all))
	{
        save_fds(&all, 2);
		if (all.line)
		{
			parser_string(&all);
			parser_cmd(&all);
			update_main(&all);
		}
		ft_putstr_fd("bash-3.2$ ", 1);
        restore_fds(&all, 2);
	}
	return (all.exit_status);
}
