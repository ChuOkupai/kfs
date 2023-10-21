/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:32:34 by jbondri           #+#    #+#             */
/*   Updated: 2023/10/21 00:15:05 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# define EOF (-1)

int	printf(const char *format, ...);
int	putchar(int ci);
int	puts(const char *str);