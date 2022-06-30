/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/06/30 23:06:25 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    ft_echo(t_exec *exec, int index)
{
    int flag;

    while(exec->command[index] && ft_is_another_flag(exec, index + 1) == WORD)
    {
        if(ft_strcmp(exec->command[index], "-n") == 0)
        {
            index++;
            flag = 1;
        }
        if(exec->command[index][0] == '$')
            index++;
        printf("%s", exec->command[index]);
        if(exec->command[index + 1])
            printf(" ");
        index++; 
    }
    if(!flag)
        printf("\n");
    return (index);
}