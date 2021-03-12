/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:20:37 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 20:15:57 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = 0;
	while (*s)
	{
		if (*s == c)
			res = (char *)s;
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	if (res)
		return (res);
	else
		return (NULL);
}
