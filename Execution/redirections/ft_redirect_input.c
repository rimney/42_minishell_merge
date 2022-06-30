/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:25 by rimney            #+#    #+#             */
/*   Updated: 2022/06/30 15:59:47 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    redirect(t_exec *exec, int command_location, int index)
{
    printf("%s <DDD<\n", exec->command[index]);
    index = open(exec->command[index], O_RDONLY);
    //printf()
    dup2(index, 0);
    close(index);
    ft_execute_command(exec, command_location);
    
}

int    ft_redirect_input(t_exec *exec, t_pipe *tpipe, int index, int command_location)
{
    int i;
    int input_file = 0;
    int pid;


    i = index;
    tpipe->fd[0] = 0;
    if(input_file == -1)
    {
        perror("minishell error");
        return 0;
    }
    if(ft_strcmp(exec->command[i], "<") == 0)
    {
  //      printf("%s << here\n", exec->command[index + 1]);
        input_file = exec->input_count + i - 1;
            pid = fork();
            if (pid == 0)
                redirect(exec, command_location, index + 1);
           
    }

    printf("%d << i\n", i);
    return (i - 1);
}