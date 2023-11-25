# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djoker <djoker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:22:02 by lrosa-do          #+#    #+#              #
#    Updated: 2023/11/25 07:39:58 by djoker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		main

CXX =		g++
CPPFLAGS =	-g -Wall    
CPPFLAGS += -g -fsanitize=address 
CPPLDFLAGS =-lasan 	-lsquirrel   -lSDL2  -lGL -lm 

OBJS_DIR	=	obj
SRCS_DIR	=	src


SRCS		=	main.cpp 
SRC_PATH 	=  src/
OBJS		=	$(addprefix ${OBJS_DIR}/, ${SRCS:.cpp=.o})


RM			=	rm -rf
MKDIR		=	mkdir -p

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CXX)      $(OBJS) -o $(NAME) $(CPPLDFLAGS)
			@echo "Linked executable \033[38;2;39;154;186m$(NAME)\033[0m"
			@./$(NAME) 
			

${OBJS_DIR}/%.o: 	${SRCS_DIR}/%.cpp	
			@${MKDIR} $(@D)
			$(CXX) -I./include  $(CPPFLAGS)  -c $< -o $@ 
			@echo "\e[91m" " Compile " "\e[0m ($<)" "\e[91m" "  object" "\e[0m ($@)"

clean:
			@$(RM) $(OBJS) $(OBJS_DIR)
			@echo "\e[91m" " Clean  obs" "\e[0m"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\e[91m" " Delete executable" "\e[0m"

re:			fclean all

.PHONY:		fclean, all, re