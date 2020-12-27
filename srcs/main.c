/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:08:51 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/27 20:49:07 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clear(t_all *all)
{
	all->env = NULL;
	all->cmd = NULL;
	all->line = NULL;
	all->pos = 0;
	all->res = 1;
}

static void	update_main(t_all *all)
{
	clear_cmd(&all->cmd);
	free(all->line);
	all->line = NULL;
	all->pos = 0;
}

int			main(int args, char **argv, char **env)
{
	t_all	all;

	(void)args;
	(void)argv;
	clear(&all);
	parser_env(&all, env);
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
	return (0);
}
