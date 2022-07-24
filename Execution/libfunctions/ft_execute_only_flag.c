/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:26:02 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 23:45:27 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_is_a_builtin(char *command)
{
	if(ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "PWD") == 0)
		return (1);
	if(ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "ECHO") == 0)
		return (1);
	if(ft_strcmp(command, "export") == 0 || ft_strcmp(command, "EXPORT") == 0)
		return (1);
	if(ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "CD") == 0)
		return (1);
	if(ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "UNSET") == 0)
		return (1);
	if(ft_strcmp(command, "env") == 0 || ft_strcmp(command, "ENV") == 0)
		return (1);
	if(ft_strcmp(command, "exit") == 0 || ft_strcmp(command, "EXIT") == 0)
		return (1);
	return (0);
}

int		ft_execute_builtin(char **parser, t_exec *exec, int index)
{
	char	**parser2;

	parser2 = ft_split(exec->command[index], ' ');
	if(ft_strcmp(parser2[0], "export") == 0)
		ft_export(exec, parser);
	if(ft_strcmp(parser2[0], "env") == 0)
		ft_env(exec);
	if(ft_strcmp(parser2[0], "exit") == 0)
		ft_exit(exec, index, parser2);
	if(ft_strcmp(parser2[0], "unset") == 0)
		ft_unset(parser, exec);
	if(ft_strcmp(parser2[0], "pwd") == 0)
		ft_pwd();
	if(ft_strcmp(parser2[0], "cd") == 0)
		ft_cd(parser[1], exec);
	if(ft_strcmp(parser2[0], "echo") == 0)
		ft_echo(parser, exec);
	else
		return (0);
	return (1);
}


int		ft_execute_builtin_parent(t_exec *exec, int index)
{
	char **parser;

	parser = ft_split_special(exec->command[0], ' ');
	ft_filter_command_double_quotes_2d_array(parser);
	if(ft_strcmp(parser[0], "export") == 0)
		ft_export(exec, parser);
	else if(ft_strcmp(parser[0], "env") == 0)
		ft_env(exec);
	else if(ft_strcmp(parser[0], "exit") == 0)
		ft_exit(exec, index, parser);
	else if(ft_strcmp(parser[0], "unset") == 0)
		ft_unset(parser, exec);
	else if(ft_strcmp(parser[0], "pwd") == 0)
		ft_pwd();
	else if(ft_strcmp(parser[0], "cd") == 0)
		ft_cd(parser[1], exec);
	else if(ft_strcmp(parser[0], "echo") == 0)
		ft_echo(parser, exec);
	else
	{
		ft_free(parser);
		return (0);
	}
	ft_free(parser);
	return (1);
}

int	ft_execute_only_flag_norm(t_exec *exec)
{
	if(only_output_redirection_flag(exec) > 0)
		ft_redirect(0, exec, 0);
	else if(only_heredoc_flag(exec) > 0)
		ft_execute_heredoc(exec, 0);
	else if(only_append_flag(exec) > 0)
		ft_append(0, exec, 0);
	else if(only_input_flag(exec) > 0)
		ft_redirect_input(1, exec, 0);
	else
		return (0);
	return (1);
}

int	ft_check_quotes_final_case(char *str)
{
	int i;

	i = 0;
	if((str[0] == '\"' && str[ft_strlen(str) - 1] != '\"')
		|| (str[0] != '\"' && str[ft_strlen(str) - 1] == '\"'))
	{
		printf("missing quotes\n");
		return (0);
	}
	return (1);
}

int quote_loop(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] != '\"')
			return (1);
		i++;
	}
	printf("minishell : command not found\n");
	return (0);
}

int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe)
{
	int pid;

	if(ft_contain(exec->command[0], '\"')
		&& (!ft_check_quotes_final_case(exec->command[0]) || !quote_loop(exec->command[0]) ))
		return (0);
	if(exec->args <= 2 && ft_execute_builtin_parent(exec, 0))
		return (1);
	if(only_command_flag(exec) > 0)
	{
		pid = fork();
		if(pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			ft_execute_command(exec, 0);
		}
		waitpid(pid, &exec->env.exit_value, 0);
		WIFEXITED(exec->env.exit_value);
    }
	else if(only_pipe_flag(exec) > 0 && exec->args > 2)
	{
		ft_assign_tpipe(tpipe, exec->pipe_count);
		execute_pipe(exec, 0, -1, tpipe);
		wait(NULL);
	}
	else if(!ft_execute_only_flag_norm(exec))
		return (0);
	return(1);
}