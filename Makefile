
NAME = minishell

LIBFT = libft.a

SRC_ = minishell.c

FORMAT_ = format.c
FORMAT = $(addprefix format/, $(FORMAT_))

ERROR_ = error.c
ERROR = $(addprefix error/, $(ERROR_))

TOKENIZER_ = tokenizer.c fsm.c
TOKENIZER = $(addprefix tokenizer/, $(TOKENIZER_))

PARSER_ = parser.c
PARSER = $(addprefix parser/, $(PARSER_))

SRC = $(addprefix srcs/, $(SRC_) $(ERROR) $(TOKENIZER) $(FORMAT) $(PARSER))


OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -L. -lft -fsanitize=address -o $(NAME) $(OBJ)

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
