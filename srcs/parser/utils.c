/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:07:49 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 18:37:25 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** append character to string
**
** @param **text pointer to string
** @param c symbol
** @return 0 if good, otherwise -1
*/

int		join_char(char **text, char c)
{
	char	*t;

	t = *text;
	if (!(*text = ft_strjoin_char(t, c)))
		return (-1);
	free(t);
	return (0);
}

/*
** join strings
**
** @param **text pointer to string
** @param *s string
** @return 0 if good, otherwise -1
*/

int		join_str(char **text, char *s)
{
	char	*t;

	t = *text;
	if (!(*text = ft_strjoin(t, s)))
		return (-1);
	free(t);
	return (0);
}

/*
** skip all spaces until a space is encountered
**
** @param *all general structure
*/

void	trim_space(t_all *all)
{
	while (all->line[all->pos] && all->line[all->pos] == ' ')
		all->pos++;
}

/*
** re-malloc arguments and add 1 empty argument
**
** @param **argv array of argument strings
** @return pointer to an array of strings, otherwise NULL
*/

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

/*
** re-malloc command arguments
**
** @param *all general structure
** @param *spec special characters
** @param *i pointer to string index
** @return 0 if good, otherwise -1
*/

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
