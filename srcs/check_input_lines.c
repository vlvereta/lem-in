/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/06/16 10:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		checkline(char **line, t_node **rooms_list)
{
	static int	com = 0;
	static int	stage = 1;

	if (*line && **line && *line[0] != 'L')
	{
		if (*line[0] == '#' && comment_or_command(*line, &com, &stage))
			return (1);
		else if (is_room(*line) && stage != 2 && (stage = 1))
			add_room_to_list(rooms_list, line, &com);
		else if (is_link(*line) && stage != 0 && (stage = 2))
			add_link_to_rooms(rooms_list, line);
		else
		{
			ft_strdel(line);
			clean_nodes(rooms_list);
			ft_printf("Something went wrong in your farm describing!\n");
			ft_printf("1 -> number_of_ants\n2 -> the_rooms\n3 -> the_links\n");
			return (0);
		}
		return (1);
	}
	ft_printf("Empty line or 'L' in the start!\n");
	ft_strdel(line);
	clean_nodes(rooms_list);
	return (0);
}

int		comment_or_command(char *line, int *com, int *stage)
{

	int		i;

	i = 0;
	if (line[1] == '#' && is_command(line))
	{
		if (*stage != 1)
			return (0);
		else
		{
			*com = (ft_strequ(line, "##start") ? 1 : *com);
			*com = (ft_strequ(line, "##end") ? 2 : *com);
			if ((*com == 1 && g_start) || (*com == 2 && g_end))
				return (0);
			*stage = 0;
		}
	}
	return (1);
}

int		is_command(char *line)
{
	if (ft_strequ(line, "##start"))
		return (1);
	if (ft_strequ(line, "##end"))
		return (1);
	return (0);
}

int		is_room(char *line)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while (line[i])
	{
		if (line[i] == '-')
			return (0);
		if (line[i] == ' ' && ++spaces)
		{
			while (line[++i] && ft_isdigit(line[i]))
				;
			if (spaces > 2 || (line[i] && line[i] != ' '))
				return (0);
			continue ;
		}
		i++;
	}
	return ((spaces == 2 ? 1 : 0));
}

int		is_link(char *line)
{
	int		i;
	int		hyphen;

	i = 0;
	hyphen = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			return (0);
		if (line[i] == '-')
		{
			hyphen++;
			if (hyphen > 1 || line[++i] == 'L' || line[i] == '#')
				return (0);
			continue ;
		}
		i++;
	}
	return ((hyphen == 1 ? 1 : 0));
}
