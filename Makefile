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

SRCS			=	src/main.c \
					src/parsing.c \
					src/init_prog.c
OBJS			= 	$(SRCS:.c=.o)

CC				= 	cc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror
NAME			= 	minishell
LIBS      		=	-L./libft -lft -lreadline 

all:			$(NAME)

$(NAME):		lib $(OBJS) 	
				$(CC) -I. $(OBJS) -o $(NAME) $(LIBS)

lib:			
				make bonus -C libft

clean:
				$(RM) $(OBJS)
				make clean -C libft

fclean:			
				$(RM) $(OBJS)
				$(RM) $(NAME)
				make fclean -C libft

re:				fclean all