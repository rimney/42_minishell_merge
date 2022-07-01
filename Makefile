# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney <rimney@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 12:27:57 by atarchou          #+#    #+#              #
#    Updated: 2022/07/01 23:45:24 by rimney           ###   ########.fr        #
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
		execution/libfunctions/command_parsing.c\
		execution/libfunctions/ft_get_env.c\
		execution/libfunctions/ft_split.c\
		execution/libfunctions/ft_strjoin.c\
		execution/libfunctions/ft_simple_strjoin.c\
		execution/libfunctions/ft_execute_command.c\
		execution/libfunctions/ft_is_another_flag.c \
		execution/libfunctions/ft_free.c\
		execution/parser/ft_fill_exec.c\
		execution/libfunctions/ft_execute_only_flag.c\
		execution/parser/ft_is_only_flag.c\
		execution/builtins/ft_echo.c\
		execution/redirections/ft_mini_redirect_output.c\
		execution/redirections/ft_middle_redirections.c\
		execution/redirections/ft_dup_and_redirect.c\
		execution/redirections/ft_mini_pipe.c\
		execution/builtins/ft_export.c \
		execution/libfunctions/ft_find_variable_index.c \
		execution/builtins/ft_env.c \


$(NAME) : $(SRCS)
			$(CC) $(SRCS) $(RL_FLAGS) $(FLAGS) -o $(NAME) 

all : $(NAME)

clean :
		rm -rf $(NAME)

fclean :
		rm -rf minishell

re : fclean all

.PHONY : all clean fclean re