/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:26:44 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/21 00:14:19 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <sys/cdefs.h>
# include <stddef.h>

int		memcmp(const void *aptr, const void *bptr, size_t size);
void	*memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size);
void	*memmove(void *dstptr, const void *srcptr, size_t size);
void	*memset(void *bufptr, int value, size_t size);
size_t	strlen(const char *str);