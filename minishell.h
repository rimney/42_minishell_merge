/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 11:57:55 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/21 16:24:05 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define GREEN_COLOR "\e[0;32m"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
typedef struct s_token
{
	struct s_token	*next;
	int				type;
	int				count;
	char			*value;
	char			quote;
}				t_token;
int				g_flag;
typedef struct s_redir
{
	int				type;
	int				count;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_tok_red
{
	t_token	*lst_token;
	t_redir	*lst_redir;
}				t_tok_red;



typedef enum e_type
{
	WORD,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
	PIPE,
}			t_type;

typedef struct s_env
{
    char    **envp;
	char	**export;
    int     exit_value;
} t_env;

typedef struct s_pipe
{
	
	int fd[2];
	int in;
	int max;
	int in_save;
	t_env *env;
} t_pipe;

typedef struct s_exec
{
	char **command;
	int input_count;
	int input_flag;
	int redirection_count;
	int redirecion_flag;
	int append_count;
	int append_flag;
	int heredoc_count;
	int heredoc_flag;
	int pipe_count;
	int pipe_flag;
	int args;
	int initial_flag;
	int sev_flag;
	int error_flag;
	int in;
    char    **envp;
	char	**export;
	t_env env;
} t_exec;

/******** utils.c functions ********/

int			ft_strcmp(char *s1, char *s2);
char		*ft_strsub(char *s,  int start, int len);
void		print_lst(t_token *lst);
void		print_redir(t_redir *lst);
char		*init_props(char *stro);

/******* utils_2.c functions ********/

size_t		ft_strlen(const char *str);
int			ft_isdigit(int c);
int			ft_isspace(int c);
int			find_end_index(char *str, char c);
char		*ft_strstr(char *str, char *to_find);

/******* utils_3.c functions ********/

int			is_operation(char c);
int			contain(char *str, char c);
int			find_char_index(char *str, char c);
char		*subtract(char *str, char *sub);
void		check_token_list_end(t_token **lst_token, int nbwords);

/******* utils_4.c functions ********/

// static char	*ft_strcpy(char *dest, char *src);
char		*ft_strdup(const char *src);
char		*protected_malloc(int size);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *str1, const void *str2, size_t n);

/******** parse_token.c functions ********/

int			ft_words(char *s, char c);
int			ft_letters(char *s, char c);
int			types(t_token *lst);
int			check_if_op(char c, char s);
void		count_words(char *s, int *count);

/******** parse_token_2.c functions ********/

int			handle_words(char *s, char c, t_token *first);
char		*remove_char(char *str, char charToRemmove);
t_token		*handle_quotes(t_token *lst, int *flag, char **s);
t_token		*handle_split(t_token *lst, int *flag, char **s, char c);

/******** parse_env.c functions ********/

int			check_env_var(char *str);
int			parse_env(t_token **lst_token);

/******** parse.c functions ********/

t_token		*token_split(t_token *first, char *s, char c);
t_tok_red	*parser(t_tok_red *lst, char *line);

/******** redir.c functions ********/

int			count_redir(t_token *lst);
int			check_if_redir(int type);
void		parse_red(t_redir **red, t_token *tok, int *counts);
t_redir		*fill_redir_lst(t_redir *lst, t_token *lst_token);

/******** signals.c functions ********/

void		handle_signals(int sig);
void		handle_sigquit(int sig);

/******** error.c fucntions ********/

int			get_size_new_line(char *str);
char		*fix_line(char *str);
char		*get_new_line(char *str, char *tab, int i, int j);
void		help_rep_redir(char str, char c, int *count, int *count_redir);
void		help_rep_pipe(char str, char c, int *count, int *count_pipe);

/******** error_2.c fucntions ********/

int			check_repitition(char *stro, char c, int count);
int			check_repitition_pipe(char *stro, char c, int count);
int			check_redir_correctness(char *str);
int			fix_diff(char *str);

/******** free_parse.c fucntions ********/
void		free_lst_token(t_token *lst);
void		free_lst_redir(t_redir *lst);
void		*handle_error(char *str);

/******** expand_quotes.c fucntions ********/

int			ft_strncmp(char *s1, char *s2, int n);
int			ft_find_last_character(char *str, char c);
int			check_if_redir_exist(char *str);
char		*ft_expand(char *expand, char **envp);
void		ft_assign_expand(t_token *token, char **envp);

/******** EXECuTIOH STILL IN PROGRESS !!!!!! ****/ 
//output
int	ft_redirect(int index, t_exec *exec, int command_location);
void	ft_advanced_redirect(int index, t_exec *exec, int fd_out, int fd_in, int location);
void	ft_single_redirect(char *argv);
//input
int	ft_redirect_input(int index, t_exec *exec, int command_location);
//void    redirect(t_exec *exec, int command_location, int index);
//pipe
int execute_pipe(t_exec *exec, int index, int in,  t_pipe *tpipe);
void    ft_redirect_after_pipe_flag(t_exec *exec, t_pipe *tpipe, int fd, int index, int in_save);
void   ft_apply_input_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index);
void    ft_apply_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index);
void	ft_pipe(int in, t_pipe *tpipe, t_exec *exec, int index);
//heredoc
int ft_execute_heredoc(t_exec *exec, int index);
void    ft_advanced_heredoc(t_exec *exec, int index, int command_location);
int ft_basic_heredoc(t_exec *exec, int index);
void ft_heredoc(t_exec *exec, int command_location, int index);
int ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_loaction);
int ft_get_last_delimiter(t_exec *exec, int index);
//append
int	ft_append(int index, t_exec *exec, int command_location);
void	ft_single_append(int argc, char **argv);
void	ft_advanced_append(int index, t_exec *exec, int fd_out, int fd_in, int location);
//count
int	ft_count_tokens(t_token *token);
void ft_count_till_last_token(t_exec *exec, t_pipe *pipes);
int	ft_count_till_other_token(t_exec *exec, int index, char *token);
// command parsing
char	*ft_exec_command(char **envp, char *command);
char	*ft_filter_command(char *command);
int	ft_count_elements(char **str);
char	*ft_locate_env(char **env);
int	ft_is_space(char *str);
//envp assignment
void    ft_get_env(t_exec *exec, char **env);
//split
char	**ft_split(char const *s, char c);
//join
char    *ft_strjoin(char *s1, char *s2, char *s3);
char	*ft_simple_strjoin(char *s1, char *s2);
//execute command
void    ft_execute_command(t_exec *exec, int index);
//free
void	ft_free(char **str);
//is_another_flag
int ft_is_another_flag(t_exec *exec, int index);
//fill_exex
void	ft_fill_exec(t_exec *exec, t_token *token);
void	ft_initialize_exec(t_exec *exec);
//execute only flag
int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe);
void	ft_assign_tpipe(t_pipe *pipe, int argc);
//only_flag
int only_pipe_flag(t_exec *exec);
int only_command_flag(t_exec *exec);
int only_output_redirection_flag(t_exec *exec);
int only_heredoc_flag(t_exec *exec);
int only_append_flag(t_exec *exec);
int only_input_flag(t_exec *exec);
void	ft_check_expand(t_exec *exec);

//mini
int	ft_mini_redirect_output(t_exec *exec, t_pipe *tpipe, int i);
int ft_apply_pipe_middle(t_exec *exec, t_pipe *tpipe, int i, int fd);
int ft_apply_redin_middle(t_exec *exec, t_pipe *tpipe,  int i);
int	ft_middle_rediout(t_exec *exec, t_pipe *tpipe, int i);
int	ft_dup_and_redirect(int fd_in, t_exec *exec, int index);
int	ft_mini_pipe(t_exec *exec, t_pipe *pipes, int in, int count, int index);
// built_ins
int	ft_mini_append(t_exec *exec, t_pipe *tpipe, int i);
int    ft_echo(char **str, t_exec *exec);
void    ft_export(t_exec *exec, char **argv);

int ft_find_variable_index(char *str, char c);
void    ft_env(t_exec *exec);
void    ft_exit(t_exec *exec, int index, char **argv);
int ft_atoi(char *str);
void    ft_unset(char *str, t_exec *exec);
void    ft_pwd(void);
void    ft_export_replace(t_exec *exec, char *arg, int index);
void    ft_cd(char *path, t_exec *exec);
int ft_path_exists(char **envp);
int	ft_mini_redirect_input(t_exec *exec, t_pipe *tpipe, int i);
int ft_advanced_redirect_input(t_exec *exec, int fd_in, int index);
int	ft_mini_heredoc(t_exec *exec, t_pipe *tpipe, int i);
int	ft_is_a_builtin(char *command);
int		ft_execute_builtin(char **parser, t_exec *exec, int index);
void	ft_minishell(t_exec *exec, t_pipe *tpipe, int index);
char	*ft_itoa(int nb);
int	ft_find_next_flag(t_exec *exec, int *index, int *fd, int *in);
int ft_contain(char *str, char c);
int ft_redi_is_last(t_exec *exec);
void    ft_advanced_heredoc_final_case(t_exec *exec, int index);
#endif