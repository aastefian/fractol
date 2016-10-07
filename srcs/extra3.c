/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 10:44:00 by svilau            #+#    #+#             */
/*   Updated: 2016/10/05 11:30:41 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>

t_list	*ft_create_elem(double cr, double ci)
{
	t_list *tmp;

	if (!(tmp = malloc(sizeof(t_list))))
		put_err();
	if (tmp)
	{
		tmp->c.r = cr;
		tmp->c.i = ci;
		tmp->next = NULL;
	}
	return (tmp);
}

void	ft_list_push_back(t_list **begin_list, double cr, double ci)
{
	t_list *list;

	list = *begin_list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_elem(cr, ci);
	}
	else
		*begin_list = ft_create_elem(cr, ci);
}

t_list	*ft_list_last(t_list *begin_list)
{
	while (begin_list->next)
	{
		begin_list = begin_list->next;
	}
	return (begin_list);
}

float	cursor_axes_coordinates_x(int x)
{
	if (x < 0 || x > DEF_WIN_WIDTH)
		return (0);
	return (((x * 4) / (float)DEF_WIN_WIDTH) - 2);
}

float	cursor_axes_coordinates_y(int y)
{
	if (y < 0 || y > DEF_WIN_HEIGHT)
		return (0);
	return (((y * 4) / (float)DEF_WIN_HEIGHT) - 2);
}
