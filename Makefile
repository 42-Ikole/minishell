
NAME = minishell

LIBFT = libft.a

SRC_ = minishell.c

FORMAT_ = format.c
FORMAT = $(addprefix format/, $(FORMAT_))

ERROR_ = error.c
ERROR = $(addprefix error/, $(ERROR_))

TOKENIZER_ = tokenizer.c fsm.c
TOKENIZER = $(addprefix tokenizer/, $(TOKENIZER_))

PARSER_ = parser.c find_replace.c environment.c remover.c expansion.c meta_check.c
PARSER = $(addprefix parser/, $(PARSER_))

EXECUTE_ = execute.c exit.c change_dir.c path_dir.c print_echo.c \
			builtin_export.c builtin_unset.c builtin_env.c \
			free_cmd.c pre_execute.c pipe.c
EXECUTE = $(addprefix execute/, $(EXECUTE_))

SRC = $(addprefix srcs/, $(SRC_) $(ERROR) $(TOKENIZER) $(FORMAT) $(PARSER) $(EXECUTE))


OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -fsanitize=address -L. -lft -o $(NAME) $(OBJ)

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
