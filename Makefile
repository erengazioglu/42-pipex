CC		= cc
NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra -g
LIBS	= libft/libft.a
INCLUDE = include/pipex.h

SRC		= \
		main.c
TESTS	= \
		perror

OBJ				:= $(SRC:%.c=obj/%.o)
TEST_OBJ		:= $(TESTS:%=obj/%.o)


all			: $(NAME)
tests		: $(TESTS:%=tests/%)

$(NAME)		: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
$(TESTS:%=tests/%)	: $(OBJ) $(TEST_OBJ) $(LIBS)
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

$(OBJ): $(SRC:%.c=src/%.c) libft/libft.a $(INCLUDE)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(@:obj/%.o=src/%.c) -o $@
$(TEST_OBJ): $(TESTS:%=tests/%.c) libft/libft.a $(INCLUDE)
	@mkdir -p obj
	echo $(@:obj/%.o=tests/%.c)
	$(CC) $(CFLAGS) -c $(@:obj/%.o=tests/%.c) -o $@


libft/libft.a:
	make -C libft
clean	: 
	rm -rf obj
fclean	: clean
	rm -f $(NAME) $(BONUS)
	rm -f libft/libft.a
re: fclean all
