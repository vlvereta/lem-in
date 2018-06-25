/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_crossing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/06/16 10:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	farm_crossing(t_node **ants)
{
	int		i;
	int		is_fin;

	while (1)
	{
		i = 0;
		is_fin = 1;
		while (i < g_ants)
		{
			if ((ants[i])->to_end && find_step(&(ants[i])))
			{
				is_fin = 0;
				ft_printf("L%d-%s ", i + 1, ants[i]->name);
			}
			i++;
		}
		if (is_fin)
			break ;
		ft_printf("\n");
	}
}

int		find_step(t_node **ant)
{
	int			on_start;
	static int	left = 0;
	t_node		*next;

	on_start = g_ants - left;
	if ((*ant)->to->is_empty || ft_strequ((*ant)->to->name, g_end->name))
		next = (*ant)->to;
	else if (on_start < g_start->to_end || !(next = find_next(*ant, on_start)))
		return (0);
	(*ant)->is_empty = '+';
	left++;
	*ant = next;
	(*ant)->is_empty = 0;
	return (1);
}

t_node	*find_next(t_node *ant, int on_start)
{
	int		min;
	t_link	*link;
	t_node	*result;

	result = NULL;
	min = INFINITY;
	link = ant->links;
	while (link)
	{
		if (link->node->to_end <= on_start && link->node->is_empty)
		{
			min = link->node->to_end;
			result = link->node;
		}
		link = link->next;
	}
	return (result);
}
