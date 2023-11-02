# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 15:58:04 by iel-mach          #+#    #+#              #
#    Updated: 2023/04/29 18:18:32 by iel-mach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++

FLAGS = -std=c++98  -Wall -Wextra -Werror #-fsanitize=address

SRC = main.cpp servdata.cpp Locationdata.cpp Utiles.cpp request.cpp socket.cpp header.cpp response.cpp cgi.cpp


all : $(NAME)

$(NAME) : $(SRC)
		@$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean : 
		@rm -f $(NAME)

fclean : clean

re : fclean all