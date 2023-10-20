/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:15:46 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/20 18:17:10 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size)
{
	unsigned char		*dst;
	const unsigned char	*src = (const unsigned char*) srcptr;

	dst = (unsigned char *) dstptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return (dstptr);
}
