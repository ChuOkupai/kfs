/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:33:45 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/21 15:43:44 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <sys/cdefs.h>
# include <stddef.h>

void	abort(void);
void *bsearch(const void *key, const void *base, size_t nmemb,
		size_t size, int (*compar)(const void *, const void *));