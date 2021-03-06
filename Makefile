NAME := ft_ssl

OBJ_DIR := ./obj/
SRC_DIR := ./src/
INC_DIR := ./inc/
LIB_DIR := ./libft/

RM = /bin/rm -rf

SRC := $(wildcard src/*)
OBJ = $(addprefix $(OBJ_DIR), $(SRC:src/%.c=%.o))

LIBFT := $(LIB_DIR)libftprintf.a
LIBFT_INC := $(LIB_DIR)inc
LIBFT_FLAGS := -lftprintf -L $(LIB_DIR)

FLAGS := -Wall -Wextra -Werror
HEADER_FLAGS := -I inc/ -I $(LIB_DIR)inc/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(LIBFT_FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:%.c
	@mkdir -p obj
	@gcc $(FLAGS) $(HEADER_FLAGS) -c $< -o $@ 
$(LIBFT):
	@make -C $(LIB_DIR)

clean: 
	@$(RM) $(OBJ_DIR)
	@make clean -C$(LIB_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_DIR)
re: fclean all

vpath %.c $(SRC_DIR)
