/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:09:35 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/17 04:09:37 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_sighandler(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \n", 1);
}

void	sigquit_sighandler(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	sigint_sighandler_child(int i)
{
    (void)i;
    ft_putstr_fd("\b\b  \n", 1);
    ft_putstr_fd("^C\n", 1);
}

void	sigquit_sighandler_child(int i)
{
    (void)i;
    ft_putstr_fd("\b\b  \b\b", 1);
    ft_putstr_fd("^\\Quit: 3\n", 1);
}

void	init_signals(t_all *all, char c)
{
    errno = 0;
    if (c == 'c')
    {
        signal(SIGINT, sigint_sighandler_child);
        signal(SIGQUIT, sigquit_sighandler_child);
        if (errno != 0)
            ft_error(NULL, strerror(errno), errno, all);
    }
    else
    {
        signal(SIGINT, sigint_sighandler);
        signal(SIGQUIT, sigquit_sighandler);
        if (errno != 0)
            ft_error(NULL, strerror(errno), errno, all);
    }
}

