CC		= cc
NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra -g
LIBS	= libft/libft.a

SRC		= \
		main.c

OBJ				:= $(SRC:%.c=obj/%.o)

all			: $(NAME)

$(NAME)		: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MANDATORY) $(LIBS) -o $@

$(OBJ): $(SRC:%.c=src/%.c) include/pipex.h libft/libft.a
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(@:obj/%.o=src/%.c) -o $@

libft/libft.a:
	make -C libft
clean	: 
	rm -rf obj
fclean	: clean
	rm -f $(NAME) $(BONUS)
	rm -f libft/libft.a
re: fclean all
