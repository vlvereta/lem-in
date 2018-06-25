/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/06/16 10:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		g_ants = 0;
t_node	*g_start = NULL;
t_node	*g_end = NULL;

int		main(void)
{
	t_node	**ants;
	t_node	*rooms_list;

	get_ants_amount();
	if ((rooms_list = get_rooms_list()))
	{
		if (!g_start || !g_end)
			ft_printf("ERROR\n");
		else if (ants_to_start(&ants))
		{
			dfs_numerate(g_end);

			// for (t_node *temp = rooms_list; temp; temp = temp->next)
			// 	ft_printf("%s, to->%s, to_end: %d\n", temp->name, (temp->to ? temp->to->name : temp->name), temp->to_end);
			// exit(0);
			if (!(g_start->to_end) || g_start->to_end == INFINITY)
				ft_printf("ERROR\n");
			else
			{
				ft_printf("\n");
				farm_crossing(ants);
			}
			ft_memdel((void **)&ants);
		}
		clean_nodes(&rooms_list);
	}
	return (0);
}

void	get_ants_amount()
{
	int		ret;
	char	*line;

	if ((ret = get_next_line(0, &line)) == -1)
	{
		perror("Bad STDIN reading");
		exit(-1);
	}
	else if (!ret)
	{
		ft_printf("File is empty!\n");
		exit(0);
	}
	if (*line && is_only_digits(line)
		&& (g_ants = ft_atoi(line)) > 0)
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
		return ;
	}
	ft_strdel(&line);
	ft_printf("No proper amount of ants was given!\n");
	exit(0);
}

int		ants_to_start(t_node ***ants)
{
	int		i;

	if ((*ants = ft_memalloc(sizeof(t_node *) * g_ants)))
	{
		i = 0;
		while (i < g_ants)
			(*ants)[i++] = g_start;
		return (1);
	}
	else
		perror("Cannot create ants array");
	return (0);
}

void	dfs_numerate(t_node *node)
{
	int		cur_dist_to_end;
	t_link	*link;

	if (node)
	{
		link = node->links;
		cur_dist_to_end = node->to_end + 1;
		while (link)
		{
			if (cur_dist_to_end < link->node->to_end)
			{
				link->node->to_end = cur_dist_to_end;
				link->node->to = node;
				dfs_numerate(link->node);
			}
			link = link->next;
		}
	}
}

void	clean_nodes(t_node **head)
{
	t_node	*temp;

	temp = *head;
	if (temp && temp->next)
		clean_nodes(&(temp->next));
	if (temp)
	{
		if (temp->links)
			clean_links(&(temp->links));
		ft_strdel(&(temp->name));
		ft_memdel((void **)&temp);
	}
}
