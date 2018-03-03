CC=clang
CFLAGS=-Wall -Wextra -g
OS := $(shell uname)
ifeq ($(OS), Darwin)
FRAMEWORKS= -lmlx -framework OpenGL -framework AppKit -framework OpenCL
else
FRAMEWORKS= -lmlx -lXext -lX11 -lm -lOpenCL
endif
FILES=main cl_wrapper
OBJ=$(addsuffix .o, $(FILES))
NAME=test

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(FRAMEWORKS)
	@echo "Binary is done! 🖥"
%.o: %.c
	@$(CC) -c $^ -o $@ $(CFLAGS)
clean:
	@rm -f $(OBJ)
	@make -C libft/ clean
	@echo "Cleaned the objects! ❌"
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "Cleaned the binary! ☠️"
re: fclean all
	
.PHONY: clean fclean re

