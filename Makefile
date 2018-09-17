# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnepfumb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/07 10:54:13 by mnepfumb          #+#    #+#              #
#    Updated: 2017/12/07 10:54:38 by mnepfumb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC =	draw.c key.c main.c raycast.c tools.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft/ fclean && make -C libft/
	gcc -Wall -Wextra -Werror -c  $(SRC)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) -L libft/ -lft -lmlx -framework OpenGL -framework AppKit 

clean:
	/bin/rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft/libft.a

re: fclean all
