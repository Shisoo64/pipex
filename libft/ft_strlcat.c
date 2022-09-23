/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:04:18 by rlaforge          #+#    #+#             */
/*   Updated: 2022/04/18 16:04:19 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	i = -1;
	if (size == 0 || dl > size)
		return (size + sl);
	if (!*src)
		return (dl);
	while (src[++i] && (dl + i) < size - 1)
		dst[dl + i] = src[i];
	dst[dl + i] = '\0';
	return (dl + sl);
}
