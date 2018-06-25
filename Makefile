# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 13:48:43 by vlvereta          #+#    #+#              #
#    Updated: 2018/04/18 13:49:06 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = lem-in

OBJ = srcs/lem_in.o srcs/check_input_lines.o srcs/get_rooms_list.o \
	srcs/farm_crossing.o srcs/helpers.o

FLAGS = -Wall -Wextra -Werror

LIBFT = make -C $(LIB_FOLDER)

LIB_FOLDER = ./libft/

all: $(NAME)

$(NAME): $(OBJ)
	@	$(LIBFT)
	@	$(CC) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) -o $@ -c $< -Iincludes $(FLAGS)

clean:
	@	make -C $(LIB_FOLDER) clean
	@	rm -f $(OBJ)

fclean: clean
	@	make -C $(LIB_FOLDER) fclean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
