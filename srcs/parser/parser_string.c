/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:03:16 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 00:22:18 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** gets strings when encountering special characters
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 1 if a special character is encountered, 0 if not, -1 error
*/

static int	get_spec(t_all *all, char **text)
{
	const char	spec[5] = "\\$\'\"";
	int			(*f[4])(t_all*, char**);
	int			i;

	i = -1;
	f[0] = get_shielding;
	f[1] = get_variables;
	f[2] = get_strong_quotes;
	f[3] = get_quotes;
	while (++i < (int)ft_strlen(spec))
	{
		if (all->line[all->pos] == spec[i])
		{
			if (f[i](all, text) == -1)
				return (-1);
			return (1);
		}
	}
	return (0);
}

/*
** gets the name of the command entered by the user
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

static int	get_name(t_all *all)
{
	const char	spec[4] = " |;";

	while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (!get_spec(all, &(cmdlast(all->cmd)->name)))
		{
			if (join_char(&(cmdlast(all->cmd)->name),
				all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	return (0);
}

/*
** gets all the arguments entered by the user
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

static int	get_arg(t_all *all)
{
	const char	spec[3] = "|;";
	int			i;

	i = 0;
	while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (all->line[all->pos] == ' ')
		{
			if (add_remalloc_argv(all, spec, &i) == -1)
				return (-1);
		}
		else
		{
			if (!get_spec(all,
				&(cmdlast(all->cmd))->argv[i]))
			{
				if (join_char(&(cmdlast(all->cmd))->argv[i],
					all->line[all->pos]) == -1)
					return (-1);
				all->pos++;
			}
		}
	}
	return (0);
}

/*
** Parses the string entered by the user
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

int			parser_string(t_all *all)
{
	t_cmd		*lst;

	while (all->line[all->pos])
	{
		if (!(lst = init_cmd()))
			return (-1);
		cmdadd_back(&all->cmd, lst);
		trim_space(all);
		if (get_name(all) == -1)
			return (-1);
		trim_space(all);
		if (get_arg(all) == -1)
			return (-1);
		if (all->line[all->pos] == '|')
			(cmdlast(all->cmd))->pipe = 1;
		all->pos++;
	}
	return (0);
}
