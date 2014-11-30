# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbert <jbert@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/18 19:08:08 by jbert             #+#    #+#              #
#    Updated: 2014/05/11 23:25:47 by jbert            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	erase

SRC		=	erase.c

OBJ		=	erase.o

FLAG	=	-Wall -Wextra -Werror -Ofast

$(NAME):
	gcc $(FLAG) -c $(SRC)
	gcc $(FLAG) -o $(NAME) $(OBJ)

all: $(NAME) 

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

re:	fclean all

.PHONY: all NAME clean fclean re

