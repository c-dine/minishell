# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 17:31:23 by ntan              #+#    #+#              #
#    Updated: 2022/03/15 16:24:05 by ntan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	src/main.c \
					src/parsing.c \
					src/init_prog.c \
					src/variable.c \
					src/signals.c
					# src/pipes.c
OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror
LIBS      		=	-L./libft -lft -lreadline
NAME			= 	minishell

.c.o:
	  			@$(CC) $(CFLAGS) -c -I. $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		lib $(OBJS)
				@echo Compiling minishell ....
				@$(CC) -I. $(OBJS) -o $(NAME) $(LIBS)
				@echo Minishell compiled.
				

lib:			
				@echo Compiling libft ....
				@make bonus -C libft
				@echo Libft compiled.

clean:
				@echo Cleaning ....
				@$(RM) $(OBJS)
				@make clean -C libft
				@echo Cleaning done.

fclean:			
				@echo Cleaning ....
				@$(RM) $(OBJS)
				@$(RM) $(NAME)
				@make fclean -C libft
				@echo Cleaning done.

re:				fclean all