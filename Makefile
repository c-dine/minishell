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

$(NAME):	libft $(OBJS) 
				  $(CC) $(CFLAGS) -I. $(OBJS) -o $(NAME) -L./libft -lft

libft:			
				make -C ./libft

clean:
				$(RM) $(OBJS)
				make clean -C libft

fclean:			
				
				$(RM) $(NAME)
				make fclean -C libft

re:				fclean all