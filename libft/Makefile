NAME = libftprintf.a

CC = gcc
RM = /bin/rm -rf

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
SRC := $(wildcard src/*)
OBJ = $(addprefix $(OBJ_DIR), $(SRC:src/%.c=%.o))

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	 @ar rc $(NAME) $(OBJ)
	 @ranlib $(NAME)
$(OBJ_DIR)%.o : %.c
	@mkdir -p obj
	@gcc $(FLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	@$(RM) $(OBJ_DIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

vpath %.c $(SRC_DIR)
