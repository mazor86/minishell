/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:03:16 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/22 01:14:42 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_f(int (**f)(t_all*, char**))
{
	f[0] = get_shielding;
	f[1] = get_variables;
	f[2] = get_strong_quotes;
	f[3] = get_quotes;
}

static int	get_spec(t_all *all, char **text)
{
	const char	spec[5] = "\\$\'\"";
	int			(*f[4])(t_all*, char**);
	int			i;

	i = -1;
	init_f(f);
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

static int	get_name(t_all *all)
{
	const char	spec[4] = " |;";

	while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (!get_spec(all, &((t_cmd*)ft_lstlast(all->cmd)->content)->name))
		{
			if (join_char(&((t_cmd*)ft_lstlast(all->cmd)->content)->name,
				all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	return (0);
}

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
				&((t_cmd*)ft_lstlast(all->cmd)->content)->argv[i]))
			{
				if (join_char(&((t_cmd*)ft_lstlast(all->cmd)->content)->argv[i],
					all->line[all->pos]) == -1)
					return (-1);
				all->pos++;
			}
		}
	}
	return (0);
}

int			parser_string(t_all *all)
{
	t_list		*lst;
	const char	spec[3] = "|;";

	while (all->line[all->pos])
	{
		if (!(lst = init_cmd()))
			return (-1);
		ft_lstadd_back(&all->cmd, lst);
		trim_space(all);
		if (ft_strchr(spec, all->line[all->pos]))
		{
			if (all->line[all->pos] == '|')
				((t_cmd*)ft_lstlast(all->cmd)->content)->pipe_start = 1;
			all->pos++;
		}
		trim_space(all);
		if (get_name(all) == -1)
			return (-1);
		trim_space(all);
		if (get_arg(all) == -1)
			return (-1);
		if (all->line[all->pos] == '|')
			((t_cmd*)ft_lstlast(all->cmd)->content)->pipe_end = 1;
	}
	return (0);
}
