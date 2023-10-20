/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:05:37 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/20 18:12:31 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*memset(void *bufptr, int value, size_t size)
{
	unsigned char	*buf;

	buf = (unsigned char *)bufptr;
	for (size_t i = 0; i < size; i++)
	{
		buf[i] = (unsigned char) value;
	}
	return (bufptr);
}
