# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 17:31:23 by ntan              #+#    #+#              #
#    Updated: 2022/03/07 17:33:35 by ntan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	src/main.c

OBJS			= 	$(SRCS:.c=.o)

CC				= 	cc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror
NAME			= 	minishell

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -I. $(SRCS) -o $(NAME) -lreadline

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all