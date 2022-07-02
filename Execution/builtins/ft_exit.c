/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:42:34 by rimney            #+#    #+#             */
/*   Updated: 2022/07/02 02:07:43 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    apply_exit(t_exec *exec)
{
    int count;

    count = 0;
    while (exec->command[count])
        count++;
    if(count > 2)
    {
        printf("minishell: exit : too many arguments\n");
        exec->env.exit_value = 1;
        return (0);
    }
    if(count == 2)
    {
        if (ft_atoi(args))
    }
}
void    ft_exit(t_exec *exec, int index)
{
    int value
    if()
    apply_exit()

}