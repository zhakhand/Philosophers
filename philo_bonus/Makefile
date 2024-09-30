SRCS = srcs/check.c srcs/ft_atoi.c srcs/ft_itoa.c \
srcs/overlord.c srcs/philo_init.c srcs/routine.c \
srcs/utils.c srcs/ft_strjoin.c philo_bonus.c

HEAD = include/philo_bonus.h 

NAME = philo_bonus

CC = cc

RM = rm -f

OBJS = ${SRCS:%.c=%.o}

CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

%.o:	%.c
		@echo "Compiling $<..."
		${CC} ${CFLAGS} -c $? -o $@

${NAME}:	philo_bonus

philo_bonus:	philo_bonus.o
		${CC} ${CFLAGS} -fsanitize=thread -g -O1 ${SRCS} -o philo_bonus -lpthread

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} philo_bonus

re:		fclean all

.PHONY:	all clean fclean re
# -fsanitize=thread -g -O1 -o program -lpthread