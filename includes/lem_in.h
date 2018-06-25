/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 10:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/05/29 10:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

# define INFINITY 2147483647

extern int				g_ants;
extern struct s_node	*g_start;
extern struct s_node	*g_end;

typedef struct		s_link
{
	struct s_node	*node;
	struct s_link	*next;
}					t_link;

typedef struct		s_node
{
	char			*name;
	int				coord_x;
	int				coord_y;
	struct s_link	*links;
	struct s_node	*to;
	int				to_end;
	char			is_empty;
	struct s_node	*next;
}					t_node;

void				get_ants_amount();
t_node				*get_rooms_list(void);
int					checkline(char **s, t_node **rooms_list);
int					is_command(char *line);
int					comment_or_command(char *line, int *com, int *stage);
t_node				*findnode(t_node **list, char *name);
int					findcoord(t_node *list, char *s_x, char *s_y);
int					findlink(t_node *one, t_node *two);
int					is_room(char *line);
void				add_room_to_list(t_node **head, char **line, int *com);
t_node				*new_room(char **t, int *com);
int					is_link(char *line);
void				add_link_to_rooms(t_node **head, char **line);
int					add_link(t_link **head, t_node *pointer);
int					ants_to_start(t_node ***ants);
void				dfs_numerate(t_node *node);
void				farm_crossing(t_node **ants);
int					find_step(t_node **ant);
t_node				*find_next(t_node *ant, int on_start);
void				clean_tab(char **tab);
void				clean_links(t_link **links);
void				clean_nodes(t_node **head);

#endif
