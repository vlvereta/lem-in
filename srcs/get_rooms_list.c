/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/06/16 10:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*get_rooms_list(void)
{
	int		r;
	char	*line;
	t_node	*rooms_list;

	rooms_list = NULL;
	while ((r = get_next_line(0, &line)))
	{
		if (r == -1)
		{
			perror("Bad STDIN reading");
			exit(-1);
		}
		ft_printf("%s\n", line);
		if (!checkline(&line, &rooms_list))
			return (NULL);
		ft_strdel(&line);
	}
	return (rooms_list);
}

void	add_room_to_list(t_node **head, char **line, int *com)
{
	char	**t;
	t_node	*new;

	if (!(t = ft_strsplit(*line, ' ')))
		perror("Input line cannot split up!\n");
	if (t && findcoord(*head, t[1], t[2]))
		ft_printf("Node with x: %s and y: %s already existed!\n", t[1], t[2]);
	else if (t && !findnode(head, t[0]))
	{
		if ((new = new_room(t, com)))
		{
			new->next = *head;
			*head = new;
			clean_tab(t);
			return ;
		}
		else
			ft_printf("Node from \'%s\' wasn't created!\n", t[0]);
		clean_tab(t);
	}
	else if (t)
		ft_printf("Duplicate name of the node \'%s\'!\n", *line);
	ft_strdel(line);
	clean_nodes(head);
	exit(0);
}

t_node	*new_room(char **t, int *com)
{
	t_node	*new;

	if ((new = ft_memalloc(sizeof(t_node))))
	{
		new->name = ft_strdup(t[0]);
		new->coord_x = ft_atoi(t[1]);
		new->coord_y = ft_atoi(t[2]);
		new->is_empty = '+';
		if (*com == 1)
			g_start = new;
		if (*com == 2)
			g_end = new;
		new->to_end = (*com == 2 ? 0 : INFINITY);
	}
	*com = 0;
	return (new);
}

void	add_link_to_rooms(t_node **head, char **line)
{
	char	**t;
	t_node	*node_1;
	t_node	*node_2;

	if (!(t = ft_strsplit(*line, '-')))
		perror("Input line cannot split up!\n");
	if (t && (node_1 = findnode(head, t[0]))
			&& (node_2 = findnode(head, t[1])))
	{
		if (findlink(node_1, node_2) && 
			ft_printf("The link \'%s\' already created!\n", *line))
			return ;
		if (add_link(&(node_1->links), node_2) &&
			add_link(&(node_2->links), node_1))
			return ;
		else
			ft_printf("Link from \'%s\' wasn't created!\n", *line);
		clean_tab(t);
	}
	else
		ft_printf("Some room's name in \'%s\' wasn't found!\n", *line);
	ft_strdel(line);
	clean_nodes(head);
	exit(0);
}

int		add_link(t_link **head, t_node *pointer)
{
	t_link	*new;

	if (!(new = ft_memalloc(sizeof(t_link))))
		return (0);
	new->node = pointer;
	new->next = *head;
	*head = new;
	return (1);
}
