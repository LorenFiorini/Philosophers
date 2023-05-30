# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 22:42:01 by lfiorini          #+#    #+#              #
#    Updated: 2023/05/30 02:23:27 by lfiorini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CC		= cc
CFLAGS	= -Werror -Wall -Wextra -pthread
INC		= -I ./includes/

FILE	= 1_main

SRC_DIR = ./sources/
OBJ_DIR = ./objects/

SRCS	= $(addprefix ${SRC_DIR}, $(addsuffix .c, $(FILES)))
OBJS	= $(addprefix ${OBJ_DIR}, $(addsuffix .o, $(FILES)))


all:	$(NAME)

$(OBJ_DIR)%.o: ${SRC_DIR}%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
