/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/10/26 13:04:32 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

int		main()
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	
	while ((ret = read(1, buf, BUFFER_SIZE)) == BUFFER_SIZE)
	{
		buf[BUFFER_SIZE] = '\0';
		printf("%s", buf);
	}
	return (0);
}
