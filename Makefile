# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney <rimney@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 12:27:57 by atarchou          #+#    #+#              #
#    Updated: 2022/07/29 02:21:06 by rimney           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -Wall -Wextra -Werror 
FLAGS =  -lreadline 
RL_FLAGS = -L /Users/atarchou/homebrew/opt/readline/lib -I /Users/atarchou/homebrew/opt/readline/include
SRCS = Parsing/parse.c\
		Parsing/redir.c\
		Parsing/parse_token.c\
		Parsing/parse_token_2.c\
		Parsing/utils.c\
		Parsing/utils_2.c\
		minishell_src/minishell.c\
		minishell_src/minishell2.c\
		minishell_src/minishell3.c\
		minishell_src/minishell4.c\
		Parsing/utils_3.c\
		Parsing/parse_env.c\
		Parsing/error.c\
		Parsing/error_2.c\
		Parsing/utils_4.c\
		Parsing/utils5.c\
		Parsing/free_parse.c\
		Parsing/expand_quotes.c\
		execution/libfunctions/ft_count_tokens.c\
		execution/redirections/heredoc/ft_heredoc.c\
		execution/redirections/heredoc/ft_heredoc2.c\
		execution/redirections/heredoc/ft_heredoc3.c\
		execution/redirections/ft_pipe.c\
		execution/redirections/ft_pipe2.c\
		execution/redirections/pipe3.c\
		execution/redirections/ft_append.c\
		execution/redirections/input/ft_redirect_input.c\
		execution/redirections/ft_redirect_output.c\
		execution/libfunctions/command_parsing.c\
		execution/libfunctions/ft_get_env.c\
		execution/libfunctions/ft_split.c\
		execution/libfunctions/ft_split2.c\
		execution/libfunctions/ft_strjoin.c\
		execution/libfunctions/ft_simple_strjoin.c\
		execution/libfunctions/ft_execute_command.c\
		execution/libfunctions/ft_is_another_flag.c \
		execution/libfunctions/ft_free.c\
		execution/parser/ft_fill_exec.c\
		execution/libfunctions/ft_execute_only_flag.c\
		execution/libfunctions/ft_execute_only_flag2.c\
		execution/parser/ft_is_only_flag.c\
		execution/parser/ft_is_only_flag2.c\
		execution/builtins/ft_echo.c\
		execution/builtins/ft_echo2.c\
		execution/redirections/ft_mini_redirect_output.c\
		execution/redirections/ft_middle_redirections.c\
		execution/redirections/ft_dup_and_redirect.c\
		execution/redirections/ft_mini_pipe.c\
		execution/builtins/ft_export.c \
		execution/builtins/ft_export2.c \
		execution/builtins/ft_export3.c \
		execution/libfunctions/ft_find_variable_index.c \
		execution/builtins/ft_env.c \
		execution/libfunctions/ft_atoi.c \
		execution/builtins/ft_exit.c \
		execution/builtins/ft_unset.c \
		execution/builtins/ft_pwd.c \
		execution/builtins/ft_cd.c \
		execution/redirections/ft_mini_append.c \
		execution/redirections/input/ft_mini_redirect_input.c \
		execution/redirections/heredoc/ft_mini_heredoc.c \
		execution/libfunctions/ft_itoa.c \
		execution/flags/ft_get_next_flag.c \
		execution/flags/ft_get_next_flag2.c \
		execution/libfunctions/ft_contain.c \
		execution/parser/ft_check_errors_rm.c \
		execution/redirections/heredoc/ft_execute_heredoc.c \
		execution/redirections/input/ft_redirect_input_final_case.c \
		execution/libfunctions/ft_open.c \
		execution/libfunctions/ft_special_split.c \
		execution/libfunctions/ft_special_split2.c \
		execution/parser/ft_filter_quotes.c \
		execution/redirections/heredoc/ft_heredoc_final_case.c \
		main.c \
		execution/redirections/heredoc/ft_find_next_flag_heredoc.c \
		

$(NAME) : $(SRCS)
			stty -echoctl
			$(CC) $(SRCS) $(RL_FLAGS) $(FLAGS) -o $(NAME) 

all : $(NAME)

clean :
		rm -rf $(NAME)

fclean :
		rm -rf minishell

re : fclean all

.PHONY : all clean fclean re