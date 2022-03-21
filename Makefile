# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdine <cdine@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 17:31:23 by ntan              #+#    #+#              #
#    Updated: 2022/03/21 12:33:06 by cdine            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	src/main.c \
					src/parsing.c \
					src/init_prog.c \
					src/variable.c \
					src/add_put.c \
					src/signals.c \
					src/open_all.c \
					src/destroy.c \
					src/process_line.c \
					src/check_cmd.c \
					src/builtins/ft_echo.c
					# src/pipes.c 
OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror -g
LIBS      		=	-L./libft -lft -lreadline
NAME			= 	minishell

.c.o:
	  			@$(CC) $(CFLAGS) -c -I. $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		lib $(OBJS)
				@echo Compiling minishell ....
				@$(CC) -I. $(OBJS) -o $(NAME) $(LIBS)
				@echo Minishell compiled.
				valgrind ./minishell
				

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