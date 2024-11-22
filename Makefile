# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagassa <smagassa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 11:18:50 by smagassa          #+#    #+#              #
#    Updated: 2024/11/22 14:19:03 by smagassa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c        \


NAME = philosophers
CC = cc
RM = rm -f
AR = ar -rc
DEPS = includes

CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(DEPS) //enleve ptetre -o


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DEPS)

clean:
	@$(RM) $(OBJS) $(OBJ_SERVER) 

fclean: clean
	@$(RM) $(CLIENT) $(SERVER) 

re: fclean all

.PHONY: re fclean all clean