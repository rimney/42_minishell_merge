/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/17 17:37:40 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_red	*init_cmd(char *line)
{
	t_tok_red	*cmd;

	cmd = (t_tok_red *)malloc(sizeof(t_tok_red));
	cmd->lst_token = (t_token *)malloc(sizeof(t_token));
	if (check_if_redir_exist(line))
		cmd->lst_redir = (t_redir *)malloc(sizeof(t_redir));
	return (cmd);
}

int	ft_mini_pipe_a(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
	fd = -1;

exec->initial_flag = 1;
while(exec->command[i + 1] != NULL)
	{
		if(ft_strcmp(exec->command[i], "|") == 0 && i == 1)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			ft_mini_pipe(exec, tpipe, -1, 0, i);
			i += exec->pipe_count;
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			fd = open(exec->command[i - 1], O_RDWR);
			i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
		}
		i++;
	}
	wait(NULL);
	return(i);
}

int		ft_minishell_executor(t_exec *exec, t_pipe *tpipe, int i, int flag)
{
	exec->initial_flag = 1;
	if(flag == REDIROUT)
	{
		ft_mini_redirect_output(exec, tpipe, i);
		return (i + exec->redirection_count);
	}
	if(flag == APPEND)
	{
		ft_mini_append(exec, tpipe, i);
		return (i + exec->append_count);
	}
	if(flag == REDIRIN)
	{
		ft_mini_redirect_input(exec, tpipe, i);
		return (i + exec->input_count);
	}
	if(flag == HEREDOC)
	{
		ft_mini_heredoc(exec, tpipe, i);
		return (i + exec->heredoc_count);	
	}
	if(flag == PIPE)
	{
		ft_mini_pipe_a(exec, tpipe, i);
		return (i + exec->pipe_count);
	}
	return (0);
}



void	ft_minishell(t_exec *exec, t_pipe *tpipe, int index)
{
	int i;
	i = index;
	
	exec->initial_flag = 0;
	ft_count_till_last_token(exec, tpipe);

	if(ft_execute_only_flag(exec, tpipe))
		 	return ;
	else
	{
		while(exec->command[i + 1] != NULL)
		{
			if(ft_strcmp(exec->command[i], ">") == 0 && exec->redirecion_flag == 0 && exec->initial_flag == 0)
				i = ft_minishell_executor(exec, tpipe, i, REDIROUT);
			if(ft_strcmp(exec->command[i], ">>") == 0 && exec->initial_flag == 0)
				i = ft_minishell_executor(exec, tpipe, i, APPEND);
			if(ft_strcmp(exec->command[i], "<<") == 0 && exec->initial_flag == 0)
				i = ft_minishell_executor(exec, tpipe, i, HEREDOC);
			if(ft_strcmp(exec->command[i], "<") == 0 && exec->initial_flag == 0)
				i = ft_minishell_executor(exec, tpipe, i, REDIRIN);
			if(ft_strcmp(exec->command[i], "|") == 0 && exec->initial_flag == 0)
				i = ft_minishell_executor(exec, tpipe, i, PIPE);
			i++;
		}
	}
	wait(NULL);
}

void	ft_test(t_token *token, char **envp, int exit_value)
{
	char *temp;

	while(token)
	{
		if(ft_strcmp(token->value, "$?") == 0 && token->value)
		{
			temp = token->value;
			token->value = ft_itoa(exit_value % 255);
			free(temp);
		}
		if(token->value[0] == '$' && token->value[1] != '?' && token->value)
		{
			temp = token->value;
			token->value = ft_expand(token->value, envp);
			free(temp);
		}
		token = token->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*temp;
	t_tok_red	*cmd;
	t_exec		exec;
	t_pipe		pipes;
	int			env_flag;

	(void)argv;
	(void)argc;
	line  = NULL;
	ft_get_env(&exec, envp);
	while (g_flag == 0)
	{
		// signal(SIGINT, handle_signals);
		// signal(SIGQUIT, SIG_IGN);
		line = readline("\e[0;32m BomusShell$>\033[0;37m");
		if (line == NULL)
			exit(0);
		if (line[0] == 0 || ft_isspace(line[0]))
		{
			free(line);
			continue ;
		}
		if (!check_redir_correctness(line))
			handle_error("error in input\n");
		add_history(line);
		cmd = 0;
		if (g_flag == 0)
		{
			temp = line;
			line = fix_line(line);
			free(temp);
			cmd = init_cmd(line);
			cmd = parser(cmd, line);
			if (!cmd)
				g_flag = 1;
		}
		ft_test(cmd->lst_token, exec.envp, exec.env.exit_value);
		ft_fill_exec(&exec, cmd->lst_token);
		ft_initialize_exec(&exec, cmd->lst_token);
		//ft_print_exec(&exec);
		ft_minishell(&exec, &pipes, 0);
		if (cmd)
		{
			if (cmd->lst_redir)
			{
				if (count_redir(cmd->lst_token) == 0)
					cmd->lst_redir = NULL;
				else
					free_lst_redir(cmd->lst_redir);
			}
			free_lst_token(cmd->lst_token);
			free(cmd);
		}
		printf("%d << exit\n", exec.env.exit_value % 255);
		ft_free(exec.command);
		g_flag = 0;
		free(line);
	}
	exit (0);
}
