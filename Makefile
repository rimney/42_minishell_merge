# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 12:27:57 by atarchou          #+#    #+#              #
#    Updated: 2022/06/30 01:21:34 by rimney           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS =  -lreadline
RL_FLAGS = -L /Users/atarchou/homebrew/opt/readline/lib -I /Users/atarchou/homebrew/opt/readline/include -g
SRCS = Parsing/parse.c\
		Parsing/redir.c\
		Parsing/parse_token.c\
		Parsing/parse_token_2.c\
		Parsing/utils.c\
		Parsing/utils_2.c\
		minishell.c\
		Parsing/utils_3.c\
		Parsing/parse_env.c\
		Parsing/error.c\
		Parsing/error_2.c\
		Parsing/utils_4.c\
		Parsing/free_parse.c\
		Parsing/expand_quotes.c\

$(NAME) : $(SRCS)
			$(CC) $(SRCS) $(RL_FLAGS) $(FLAGS) -o $(NAME) 

all : $(NAME)

clean :
		rm -rf $(NAME)

fclean :
		rm -rf minishell

re : fclean all

.PHONY : all clean fclean re