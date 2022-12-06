# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omsanfor <omsanfor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 18:03:41 by omsanfor          #+#    #+#              #
#    Updated: 2022/06/26 18:03:42 by omsanfor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c ft_putnbr_fd.c	init_data.c philo_utils.c strutils.c

SRCS_DIR = src/

OBJS = ${addprefix ${SRCS_DIR}, ${SRC:.c=.o}}

HEADER = src/philo.h

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

REMOVE = rm -f

.PHONY: all clean fclean re bonus

%.o:%.c		${HEADER}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADER}
			@${CC}	${OBJS} -o ${NAME}
			@echo "philo compiled successfully!"

bonus:		${NAME}

all:		${NAME}

fclean:		
			@${RM} ${OBJS} ${NAME}
			@echo "fclean successfully!"

clean:		
			@${RM} ${OBJS}
			@echo "fclean successfully!"

re: fclean all