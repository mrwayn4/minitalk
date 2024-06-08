# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 09:39:13 by ibouram           #+#    #+#              #
#    Updated: 2024/06/08 19:56:18 by ibouram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
NAME = client
SERVERB = server_bonus
CLIENTB = client_bonus

CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRCC = client.c
SRCS = server.c

SRCCB = client_bonus.c utils_bonus.c
SRCSB = server_bonus.c utils_bonus.c

OBJC = $(SRCC:.c=.o)
OBJS = $(SRCS:.c=.o)

OBJCB = $(SRCCB:.c=.o)
OBJSB = $(SRCSB:.c=.o)

all: $(SERVER) $(NAME)

$(SERVER): $(OBJS)
		$(CC) $(FLAGS) $^ -o $@
$(NAME): $(OBJC)
		$(CC) $(FLAGS) $^ -o $@

bonus: $(SERVERB) $(CLIENTB)

$(SERVERB): $(OBJSB)
		$(CC) $(FLAGS) $^ -o $@
$(CLIENTB): $(OBJCB)
		$(CC) $(FLAGS) $^ -o $@

%.o: %.c minitalk.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJC)
	$(RM) $(OBJSB)
	$(RM) $(OBJCB)

fclean: clean
	$(RM) $(SERVER)
	$(RM) $(NAME)
	$(RM) $(SERVERB)
	$(RM) $(CLIENTB)

re: fclean all bonus