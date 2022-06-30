# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 12:27:57 by atarchou          #+#    #+#              #
#    Updated: 2022/06/30 16:20:49 by rimney           ###   ########.fr        #
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
		execution/libfunctions/ft_count_tokens.c\
		execution/redirections/ft_heredoc.c\
		execution/redirections/ft_pipe.c\
		execution/redirections/ft_append.c\
		execution/redirections/ft_redirect_input.c\
		execution/redirections/ft_redirect_output.c\

$(NAME) : $(SRCS)
			$(CC) $(SRCS) $(RL_FLAGS) $(FLAGS) -o $(NAME) 

all : $(NAME)

clean :
		rm -rf $(NAME)

fclean :
		rm -rf minishell

re : fclean all

.PHONY : all clean fclean re