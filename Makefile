SRCS = srcs/check.c srcs/ft_atoi.c srcs/ft_itoa.c \
srcs/overlord.c srcs/philo_init.c srcs/routine.c \
srcs/utils.c philo.c

HEAD = include/philo.h 

NAME = philo

CC = cc

RM = rm -f

OBJS = ${SRCS:%.c=%.o}

CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

%.o:	%.c
		@echo "Compiling $<..."
		${CC} ${CFLAGS} -c $? -o $@

${NAME}:	philo

philo:	philo.o
		${CC} ${CFLAGS} -g ${SRCS} -o philo

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} philo

re:		fclean all

.PHONY:	all clean fclean re