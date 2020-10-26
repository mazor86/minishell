/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/10/26 13:11:45 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

int		main()
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	
	while ((ret = read(0, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		printf("%s", buf);
	}
	return (0);
}
