/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 15:35:36 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 11:35:29 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	else
		return (1);
}
