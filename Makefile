# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 09:39:13 by ibouram           #+#    #+#              #
#    Updated: 2024/04/03 01:13:27 by ibouram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SERVERB = server_bonus
CLIENTB = client_bonus

CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRCC = client.c
SRCS = server.c

SRCCB = client_bonus.c utils_bonus.c
SRCSB = server_bonus.c

OBJC = $(SRCC:.c=.o)
OBJS = $(SRCS:.c=.o)

OBJCB = $(SRCCB:.c=.o)
OBJSB = $(SRCSB:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJS)
		$(CC) $(FLAGS) $^ -o $@
$(CLIENT): $(OBJC)
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
	$(RM) $(CLIENT)
	$(RM) $(SERVERB)
	$(RM) $(CLIENTB)

re: fclean all bonus