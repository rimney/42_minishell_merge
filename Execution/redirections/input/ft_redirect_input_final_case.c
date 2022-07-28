/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input_final_case.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:11:11 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 01:13:53 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_find_next_flag2(t_exec *exec, int *index, int *in, int *fd)
{
	*in = *in;
	if (exec->command[*index + 1]
		&& ft_is_another_flag(exec, *index + 1) == REDIROUT)
		*fd = open(exec->command[*index + 2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->command[*index + 1]
		&& ft_is_another_flag(exec, *index + 1) == APPEND)
		*fd = open(exec->command[*index + 2],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (exec->command[*index + 1]
		&& ft_is_another_flag(exec, *index + 1) == REDIRIN)
		*in = open(exec->command[*index + 2], O_RDONLY);
	if (exec->command[*index + 1]
		&& ft_is_another_flag(exec, *index + 1) == HEREDOC)
		*in = open(exec->command[*index + 2], O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	ft_minishell_input_final_case_2_args(t_exec *exec)
{
	int		pid;
	char	**parser;
	int		in;

	parser = ft_split(exec->command[1], 1);
	pid = fork();
	if (pid == 0)
	{
		in = open(parser[0], O_RDONLY);
		if (in == -1)
		{
			perror("minishell : ");
			exit(1);
		}
		dup2(in, 0);
		close(in);
		execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
	}
	else
	{
		waitpid(pid, 0, 0);
		ft_free(parser);
	}
}

void	ft_input_child(t_exec *exec, int in, int fd, char **parser)
{
	in = open(parser[0], O_RDONLY);
	dup2(in, 0);
	close(in);
	if (fd != -1)
	{
		dup2(fd, 1);
		close(fd);
	}
	execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
}

void	ft_apply_minishell_input_case(t_exec *exec,
	int pid, int index, char **parser)
{
	int		in;
	int		fd;

	fd = -1;
	in = open(parser[0], O_RDONLY);
	ft_find_next_flag2(exec, &index, &in, &fd);
	if (in == -1)
	{
		perror("minishell : ");
		return ;
	}
	exec->in = in;
	pid = fork();
	if (pid == 0)
		ft_input_child(exec, in, fd, parser);
	else
	{
		waitpid(pid, 0, 0);
		ft_free(parser);
	}
}

int	ft_minishell_input_final_case(t_exec *exec, int index)
{
	char	**parser;
	int		pid;
	int		in;

	pid = -1;
	parser = ft_split(exec->command[1], 1);
	in = open(parser[0], O_RDONLY);
	exec->in = in;
	if (exec->args == 2)
	{
		ft_minishell_input_final_case_2_args(exec);
		ft_free(parser);
		return (index);
	}
	if (exec->command[2] && ft_is_another_flag(exec, 2) == PIPE)
	{
		ft_free(parser);
		return (index);
	}
	else
		ft_apply_minishell_input_case(exec, pid, index, parser);
	return (index);
}
