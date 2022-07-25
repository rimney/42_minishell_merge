/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:41:35 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 06:26:08 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pipe_condition(int index, t_exec *exec)
{
	if (exec->command[index + 1]
		&& (ft_strcmp(exec->command[index + 1], ">") == 0
			|| ft_strcmp(exec->command[index + 1], ">>") == 0
			|| ft_strcmp(exec->command[index + 1], "<") == 0)
		&& exec->pipe_count > 2)
		return (1);
	return (0);
}

// void	ft_launch_pipe(t_exec *exec, t_pipe *tpipe, *in_save,)
// {
	
// 	if (exec->command[index + 1] != NULL)
// 	{
// 		pipe(tpipe->fd);
// 		in_save = tpipe->fd[0];
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_pipe(in, tpipe, exec, index);
// 		exit(0);
// 	}
// }

int execute_pipe(t_exec *exec, int index, int in,  t_pipe *tpipe)
{
	int in_save;
	int pid;
    int fd;

    fd = -1;
    if (exec->command[index + 1] != NULL)
    {
        pipe(tpipe->fd);
        in_save =  tpipe->fd[0];
    }
    pid = fork();
    if (pid == 0)
    {
		ft_pipe(in, tpipe, exec, index);
		exit(0);
    }
    if (in != -1)
        close(in);
    if (tpipe->fd[1] !=  -1)
        close(tpipe->fd[1]);
 	if (ft_pipe_condition(index, exec))
	{
		ft_redirect_after_pipe_flag(exec, tpipe, index - 2, index, in_save);
		exec->redirecion_flag = 0;
		return (index);
	}
    if (index < tpipe->max)
    {
        if((exec->pipe_flag) && index == tpipe->max - 2)
            ft_redirect_after_pipe_flag(exec, tpipe, index , index,  in_save);
        execute_pipe(exec, index + 2, in_save , tpipe);
    }
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
    return index;
}
