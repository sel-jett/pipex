bon = pipex_bonus/
SRC = my_malloc.c utils_2.c utils.c main.c
SRCB =  $(bon)utils_2_bonus.c $(bon)utils_bonus.c $(bon)handler_bonus.c \
		$(bon)my_malloc_bonus.c $(bon)get_next_line.c \
		$(bon)get_next_line_utils.c $(bon)here_doc.c $(bon)main_bonus.c
OBJ = ${SRC:.c=.o}
OBJB = ${SRCB:.c=.o}
CC = cc
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
NAME = pipex
BNAME = pipex_bon

all: ${NAME}

bonus: ${BNAME}

%_bonus.o: %_bonus.c $(bon)pipexbonus.h
	@echo "Compiling bonus $<"
	@${CC} ${FLAGS} -c $< -o $@

%o : %c pipex.h
	@echo "Compiling $<"
	@${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	@echo "linking $@"
	@${CC} ${FLAGS} ${OBJ} -o $@

${BNAME} : ${OBJB}
	@echo "linking $@"
	@${CC} ${FLAGS} ${OBJB} -o $@

re: fclean bonus

clean:
	@rm -f ${OBJ} ${OBJB}

fclean: clean
	@rm -f ${NAME} ${BNAME}
