/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:19:37 by mazor             #+#    #+#             */
/*   Updated: 2021/03/13 02:44:51 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	res = dest;
	res1 = (unsigned char *)src;
	if (res < res1)
		while (n--)
			*(res++) = *(res1++);
	else
		while (n > i++)
			res[n - i] = res1[n - i];
	return (dest);
}
