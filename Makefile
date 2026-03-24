CC		= cc
NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra -g
LIBS	= libft/libft.a
INCLUDE = include/pipex.h

SRC		= \
		main.c \
		child.c \
		helper.c
TESTS	= \
		perror \
		fd \
		fork \
		fork2 \
		pipe \
		pipe2 \
		ipc \
		read_fd \
		execve \
		envp

OBJ				:= $(SRC:%.c=obj/%.o)
TEST_OBJ		:= $(TESTS:%=obj/%.o)

all			: $(NAME)
tests		: $(TESTS:%=tests/%)

$(NAME)		: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
$(TESTS:%=tests/%)	: $(TEST_OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(@:tests/%=obj/%.o) $(LIBS) -o $@

$(OBJ): $(SRC:%.c=src/%.c) libft/libft.a $(INCLUDE)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(@:obj/%.o=src/%.c) -o $@
$(TEST_OBJ): $(TESTS:%=tests/%.c) libft/libft.a $(INCLUDE)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(@:obj/%.o=tests/%.c) -o $@

libft/libft.a:
	make -C libft
clean	: 
	rm -rf obj
fclean	: clean
	rm -f $(NAME) $(BONUS)
	rm -f libft/libft.a
re: fclean all
