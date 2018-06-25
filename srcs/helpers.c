/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/06/16 10:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*findnode(t_node **list, char *name)
{
	t_node	*temp;

	temp = *list;
	while (temp)
	{
		if (ft_strequ(temp->name, name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int		findcoord(t_node *list, char *s_x, char *s_y)
{
	int		x;
	int		y;
	t_node	*temp;

	temp = list;
	x = ft_atoi(s_x);
	y = ft_atoi(s_y);
	while (temp)
	{
		if (temp->coord_x == x && temp->coord_y == y)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int		findlink(t_node *one, t_node *two)
{
	t_link	*temp;

	if (one && two)
	{
		temp = one->links;
		while (temp)
		{
			if (ft_strequ(two->name, temp->node->name))
				return (1);
			temp = temp->next;
		}
		temp = two->links;
		while (temp)
		{
			if (ft_strequ(one->name, temp->node->name))
				return (1);
			temp = temp->next;
		}
	}
	return (0);
}

void	clean_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_strdel(&(tab[i++]));
	ft_memdel((void **)tab);
}

void	clean_links(t_link **head)
{
	t_link	*temp;

	temp = *head;
	if (temp && temp->next)
		clean_links(&(temp->next));
	if (temp)
	{
		ft_memdel((void **)&temp);
	}
}
