# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 11:18:50 by smagassa          #+#    #+#              #
#    Updated: 2025/01/14 00:49:45 by smagassa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c        \
		src/actions.c      \
		src/creations.c     \
		src/deaths.c       \
		src/deleting.c     \
		src/forks_states.c \
		src/init_and_print.c \
		src/libft.c        \
		src/philo.c

NAME = philosophers
CC = cc
RM = rm -f
AR = ar -rc
DEPS = includes

CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(DEPS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DEPS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: re fclean all clean