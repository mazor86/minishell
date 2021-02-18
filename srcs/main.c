/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by mazor             #+#    #+#             */
/*   Updated: 2021/02/18 09:21:46 by mazor            ###   ########.fr       */
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
	all->semicol = 0;
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
	if (all->semicol == 0)
	{
		free(all->line);
		all->line = NULL;
	}
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
	init_signals(&all, 'p');
	ft_putstr_fd(PROMPT, 1);
	save_fds(&all, 2);
	while (1)
	{
		if (!all.line)
			get_next_line(0, &all.line, &all);
		if (all.line)
		{
		    if (!check_syntax(&all))
            {
                parser_string(&all);
                parser_cmd(&all);
            }
            update_main(&all);
            ft_putstr_fd("\b\b  \b\b", 1);
            ft_putstr_fd(PROMPT, 1);
		}
		else
        {
            ft_putstr_fd("\b\b  \b\b", 1);
            ft_putstr_fd(PROMPT, 1);
        }
		restore_fds(&all, 2);
	}
}

