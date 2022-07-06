/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:26:02 by rimney            #+#    #+#             */
/*   Updated: 2022/07/06 06:06:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// void	ft_execute_builtin(t_exec *exec, char **parser, int index)
// {
// 	ft_export(exec, parser, 0);
// }


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
	if(ft_strncmp(parser[0], "export", 6) == 0)
	{
		ft_export(exec, parser, index);
		return (1);
	}
	if(ft_strncmp(parser[0], "env", 3) == 0)
	{
		ft_env(exec);
		return (1);
	}
	if(ft_strncmp(parser[0], "exit", 4) == 0)
	{
		ft_exit(exec, index, parser);
		return (1);
	}
	if(ft_strncmp(parser[0], "unset", 5) == 0)
	{
		ft_unset(parser[1], exec);
		return (1);
	}
	if(ft_strcmp(parser[0], "pwd") == 0)
	{
		ft_pwd(exec->envp);
		return (1);
	}
	if(ft_strncmp(parser[0], "cd", 2) == 0)
	{
		ft_cd(parser[1], exec);
		return (1);
	}
	if(ft_strncmp(parser[0], "echo", 4) == 0)
	{
		ft_echo(parser, 0);
		return (1);
	}
	return (0);
}

int		ft_execute_builtin_parent(t_exec *exec, int index)
{
	char **parser;

	parser = ft_split(exec->command[0], ' ');
	if(ft_strncmp(parser[0], "export", 6) == 0)
	{
		ft_export(exec, parser, index);
		return (1);
	}
	if(ft_strncmp(parser[0], "env", 3) == 0)
	{
		ft_env(exec);
		return (1);
	}
	if(ft_strncmp(parser[0], "exit", 4) == 0)
	{
		ft_exit(exec, index, parser);
		return (1);
	}
	if(ft_strncmp(parser[0], "unset", 5) == 0)
	{
		ft_unset(parser[1], exec);
		return (1);
	}
	if(ft_strcmp(parser[0], "pwd") == 0)
	{
		ft_pwd(exec->envp);
		return (1);
	}
	if(ft_strncmp(parser[0], "cd", 2) == 0)
	{
		ft_cd(parser[1], exec);
		return (1);
	}
	if(ft_strncmp(parser[0], "echo", 4) == 0)
	{
		ft_echo(parser, 0);
		return (1);
	}
	ft_free(parser);
	return (0);
}

int	ft_minishell_final_case_input(t_exec *exec, t_pipe *tpipe)
{
	int i;
	int fd;
	char **parser;
	int pid;

	parser = ft_split(exec->command[1], ' ');
	if(ft_is_another_flag(exec, 0) == REDIRIN)
	{
		printf("%s <<<<<\n", parser[0]);
		fd = open(parser[0], O_RDONLY);
		if(fd == -1)
		{
			perror("minishell : ");
			exec->env.exit_value = 1;
			return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			dup2(fd, 0);
			close(fd);
			execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
		}
	}
	ft_free(parser);
	return (1);
}

int	ft_minishell_final_case(t_exec *exec, t_pipe *tpipe)
{
	int i;

	i = 0;
	if(ft_strcmp(exec->command[0], "<") == 0)
	{
		ft_minishell_final_case_input(exec, tpipe);
		return (1);
	}
	if(ft_strcmp(exec->command[0], ">") == 0)
		printf("case output\n");
	if(ft_strcmp(exec->command[0], "<<") == 0)
		printf("case heredoc\n");
	if(ft_strcmp(exec->command[0], ">>") == 0)
		printf("case append\n");
	return (0);
}


int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe)
{
	int pid;
	if(exec->args <= 2 && ft_execute_builtin_parent(exec, 0))
		return (1);
	if(ft_minishell_final_case(exec, 0))
		return (1);
	if(only_command_flag(exec) > 0)
	{
		pid = fork();
		if(pid == 0)
			ft_execute_command(exec, 0);
		waitpid(pid, &exec->env.exit_value, 0);
		WIFEXITED(exec->env.exit_value);
    }
	else if(only_pipe_flag(exec) > 0 && exec->args > 2)
	{
		ft_assign_tpipe(tpipe, exec->pipe_count);
		execute_pipe(exec, 0, -1, tpipe);
		wait(NULL);
	}
	else if(only_output_redirection_flag(exec) > 0)
		ft_redirect(1, exec, 0);
	else if(only_heredoc_flag(exec) > 0)
		ft_execute_heredoc(exec, 1);
	else if(only_append_flag(exec) > 0)
	{
		ft_append(1, exec, 0); // segfault here !!!!!
	}
	else if(only_input_flag(exec) > 0)
		ft_redirect_input(exec, 0, 0);
	else
		return (0);

	return(1);
}