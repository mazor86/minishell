/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:07:49 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/22 10:29:43 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		join_char(char **text, char c)
{
	char	*t;

	t = *text;
	if (!(*text = ft_strjoin_char(t, c)))
		return (-1);
	free(t);
	return (0);
}

int		join_str(char **text, char *s)
{
	char	*t;

	t = *text;
	if (!(*text = ft_strjoin(t, s)))
		return (-1);
	free(t);
	return (0);
}

void	trim_space(t_all *all)
{
	while (all->line[all->pos] && all->line[all->pos] == ' ')
		all->pos++;
}

char	**remalloc_args(char **argv)
{
	int		i;
	char	**res;

	i = 0;
	while (argv[i])
		i++;
	if (!(res = ft_calloc(i + 2, sizeof(char*))))
		return (NULL);
	i = -1;
	while (argv[++i])
	{
		if (!(res[i] = ft_strdup(argv[i])))
			return (NULL);
		free(argv[i]);
	}
	free(argv);
	if (!(res[i] = ft_strdup("")))
		return (NULL);
	res[i + 1] = 0;
	return (res);
}

int		add_remalloc_argv(t_all *all, const char *spec, int *i)
{
	trim_space(all);
	if (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
	{
		if (!(((t_cmd*)(ft_lstlast(all->cmd)->content))->argv =
			remalloc_args(((t_cmd*)(ft_lstlast(all->cmd)->content))->argv)))
			return (-1);
		(*i)++;
	}
	return (0);
}
