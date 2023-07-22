# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 22:42:01 by lfiorini          #+#    #+#              #
#    Updated: 2023/07/22 23:13:29 by lfiorini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo_bonus

CC				= cc
CFLAGS			= -Werror -Wall -Wextra -pthread
INC				= -I ./include/

MODE			= none
ifeq ($(MODE), pretty)
	CFLAGS		+= -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
	CFLAGS		+= -D DEBUG_FORMATTING=1 -fsanitize=address -g
endif

FILES			= 1_main_bonus\
				2_parse_args_bonus\
				3_init_philo_bonus\
				4_philosopher_bonus\
				5_death_bonus\
				6_ipc_bonus\
				exits_bonus\
				output_bonus\
				time_bonus\
				utils2_bonus\
				utils_bonus

SRC_DIR			= ./source/
OBJ_DIR			= ./objects/

SRCS			= $(addprefix ${SRC_DIR}, $(addsuffix .c, $(FILES)))
OBJS			= $(addprefix ${OBJ_DIR}, $(addsuffix .o, $(FILES)))

all:			$(NAME)

$(OBJ_DIR)%.o:	${SRC_DIR}%.c
				$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):
				mkdir -p $(OBJ_DIR)
				$(MAKE) $(OBJS)
				$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

clean:
				rm -rf $(OBJ_DIR)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY: all re clean fclean
