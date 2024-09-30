SRCS = srcs/check.c srcs/ft_atoi.c srcs/ft_itoa.c \
srcs/overlord.c srcs/philo_init.c srcs/routine.c \
srcs/utils.c srcs/time.c srcs/philo.c

HEAD = include/philo.h 

NAME = philo

CC = cc

RM = rm -f

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g

all: ${NAME}

%.o:	%.c
		@echo "Compiling $<..."
		${CC} ${CFLAGS} -c $< -o $@

${NAME}: $(OBJS)
		${CC} ${CFLAGS} ${OBJS} -o $@

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} philo

re:		fclean all

.PHONY:	all clean fclean re
# Too slow with valgrind for some reason so to check for data races use this commands
# -fsanitize=thread -g -O1 -o program -lpthread