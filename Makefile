# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdine <cdine@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 17:31:23 by ntan              #+#    #+#              #
#    Updated: 2022/04/05 18:20:49 by cdine            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	src/main.c \
					src/parsing/parsing.c \
					src/parsing/cleaning.c \
					src/parsing/multiputing.c \
					src/init_prog.c \
					src/variable/alias_expansion.c \
					src/variable/get_size_vars.c \
					src/variable/var_utils.c \
					src/add_put.c \
					src/signals.c \
					src/open_all/open_all.c \
					src/open_all/open_other.c \
					src/destroy.c \
					src/process_line/process_line.c \
					src/process_line/process_utils.c \
					src/process_line/fork.c \
					src/check_cmd/check_cmd_utils.c \
					src/check_cmd/check_cmd.c \
					src/check_cmd/put_info_check.c \
					src/heredoc/heredoc.c \
					src/heredoc/heredoc_utils.c \
					src/heredoc/heredoc_parse.c \
					src/builtins/ft_echo.c \
					src/builtins/ft_export.c \
					src/builtins/ft_export_2.c \
					src/builtins/ft_export_3.c \
					src/builtins/ft_unset.c \
					src/builtins/ft_cd.c \
					src/builtins/ft_exit.c \
					src/hd_list/hd_lstnew.c \
					src/quotes.c
					# src/pipes.c 
OBJS			= 	$(SRCS:.c=.o)

CC				= 	cc
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
				@# valgrind --suppressions=./.readline.supp --leak-check=full ./minishell

lib:			
				@echo Compiling libft ....
				@make bonus -sC libft
				@echo "Libft compiled.\n"

clean:
				@echo Cleaning ....
				@$(RM) $(OBJS)
				@make clean -sC libft
				@echo "Cleaning done.\n"

fclean:			
				@echo Cleaning ....
				@$(RM) $(OBJS)
				@$(RM) $(NAME)
				@make fclean -sC libft
				@echo "Cleaning done.\n"

re:				fclean all