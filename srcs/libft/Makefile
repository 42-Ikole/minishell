# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ivan-tol <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 14:18:51 by ivan-tol      #+#    #+#                  #
#    Updated: 2020/10/06 13:09:35 by ikole         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =  libft.a

SRC =   	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			get_next_line.c ft_skipspace.c ft_iswhitespace.c

OBJ = $(SRC:.c=.o)

BONUS_SRC =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		   	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)


CFLAGS = -Wall -Wextra -Werror

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -c $(CFLAGS) $? -o $@ -I.

bonus: $(NAME) $(BONUS_OBJ)
	ar rc $(NAME) $(BONUS_OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(BONUS_OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
