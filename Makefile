# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 17:31:23 by ntan              #+#    #+#              #
#    Updated: 2022/04/11 14:22:48 by ntan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	src/main.c \
					src/parsing/parsing.c \
					src/parsing/check_pipe_parse_error.c \
					src/parsing/parsing_2.c \
					src/parsing/cleaning.c \
					src/parsing/cleaning_2.c \
					src/parsing/multiputing.c \
					src/parsing/multiputing_2.c \
					src/init_prog.c \
					src/error.c \
					src/variable/alias_expansion.c \
					src/variable/get_size_vars.c \
					src/variable/var_utils.c \
					src/add_put.c \
					src/signals.c \
					src/open_all/open_all.c \
					src/open_all/open_fds.c \
					src/open_all/open_other.c \
					src/destroy.c \
					src/process_line/process_line.c \
					src/process_line/process_utils.c \
					src/process_line/fork.c \
					src/process_line/fork_builtins.c \
					src/check_cmd/check_cmd_utils.c \
					src/check_cmd/check_cmd.c \
					src/check_cmd/put_info_check.c \
					src/heredoc/heredoc.c \
					src/heredoc/heredoc_utils.c \
					src/heredoc/heredoc_parse.c \
					src/builtins/ft_echo.c \
					src/builtins/ft_pwd.c \
					src/builtins/ft_env.c \
					src/builtins/ft_export_0.c \
					src/builtins/ft_export_1.c \
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
	  			$(CC) $(CFLAGS) -c -I. $< -o $(<:.c=.o)

all:			lib $(NAME)

$(NAME):		$(OBJS)		
				$(CC) $(CFLAGS) -I. $(OBJS) -o $(NAME) $(LIBS)

lib:			
				make -C libft

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
