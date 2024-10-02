GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m
BLUE=\033[34m
BACK=\033[42m
BOLD=\033[1m
RESET=\033[0m

SRCS = srcs/check.c srcs/ft_itoa.c srcs/overlord.c \
srcs/philo_init.c srcs/routine.c srcs/utils.c srcs/philo_bonus.c

HEAD = include/philo_bonus.h 

NAME = philo_bonus

CC = cc

RM = rm -f

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread -O1

all: ${NAME}

%.o:	%.c
		@echo "${BLUE}${BOLD}Compiling $<${RESET}"
		@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		@${CC} ${CFLAGS} ${OBJS} -o $@ 
		@echo "${BACK}${RED}${BOLD} Successfuly built ${NAME} ${RESET}"

clean:
		@echo "${YELLOW}${BOLD}Deleting object files${RESET}" 
		@${RM} ${OBJS}

fclean: clean
		@echo "${RED}${BOLD}Deleting executable${RESET}"
		@${RM} philo_bonus

re:		fclean all

.PHONY:	all clean fclean re
# -fsanitize=thread -g -O1 -o program -lpthread