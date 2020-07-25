
NAME = minishell

LIBFT = libft.a

SRC_ = minishell.c

ERROR_ = error.c
ERROR = $(addprefix error/, $(ERROR_))

TOKENIZER_ = tokenizer.c
TOKENIZER = $(addprefix tokenizer/, $(TOKENIZER_))

SRC = $(addprefix srcs/, $(SRC_) $(ERROR) $(TOKENIZER))

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -L. -lft -o $(NAME) $(OBJ)

$(LIBFT):
	@printf "\e[0;34mCompiling LIBFT $<\n\e[0;35m"
	@cd srcs/libft && make bonus
	@mv srcs/libft/$(LIBFT) .

%.o: %.c
	@printf "\e[0;34mCompiling $<\n\e[0;35m"
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

test: all
	@printf "\e[0;0m"
	./minishell

re: fclean all

clean:
	@cd srcs/libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@rm -f libft.a
	@rm -f $(NAME)
