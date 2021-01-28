/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:     mazor <mazor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 09:21:25 by mazor             #+#    #+#             */
/*   Updated: 2020/12/03 21:30:18 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(res, (char *)&s[start], len + 1);
	return (res);
}
