/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:17:28 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/20 18:20:28 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*memmove(void *dstptr, const void *srcptr, size_t size)
{
	unsigned char			*dst;
	const unsigned char		*src = (const unsigned char *) srcptr;

	dst = (unsigned char *) dstptr;
	if (dst < src)
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
	else
	{
		for (size_t i = size; i != 0; i--)
			dst[i - 1] = src[i - 1];
	}
	return (dstptr);
}
