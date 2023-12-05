SRC = utils_2.c utils.c main.c
OBJ = ${SRC:.c=.o}
CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = pipex

all: ${NAME}

%o : %c pipex.h
	@echo "linking $<"
	@${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ} pipex.h
	@echo "linking $@"
	@${CC} ${FLAGS} ${OBJ} -o $@

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

