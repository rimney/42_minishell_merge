/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 05:01:50 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
			if(ft_strcmp(exec->command[i], ">") == 0 && exec->initial_flag == 0)
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
	t_tok_red	*cmd;
	t_exec		exec;
	t_pipe		pipes;
	int			err_flag;

	err_flag = 0;
	(void)argv;
	(void)argc;
	line  = NULL;
	
	ft_get_env(&exec, envp);
	while (g_flag == 0)
	{
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		line = handle_line_error();
		if (line[0] == 0 || ft_isspace(line[0]))
		{
			free(line);
			continue ;
		}
		if (!check_redir_correctness(line))
		{
			err_flag = 1;
			handle_error("error in input\n");
		}
		add_history(line);
		cmd = 0;
		if (g_flag == 0)
			handle_cmd_props(&line, &cmd);
		if(!err_flag && !g_flag)
		{
		ft_test(cmd->lst_token, exec.envp, exec.env.exit_value);
		 ft_fill_exec(&exec, cmd->lst_token);
		ft_initialize_exec(&exec);
		ft_minishell(&exec, &pipes, 0);
		}
		if (cmd)
			free_and_free(cmd);
		if(!err_flag && !g_flag)
			ft_free(exec.command);
		g_flag = 0;
		free(line);
		err_flag = 0;
	}
	exit (0);
}
