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

void	init_signals(t_all *all)
{
    signal(SIGINT, sigint_sighandler);
    signal(SIGQUIT, sigquit_sighandler);
}
