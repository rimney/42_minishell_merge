/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/06 05:11:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_echo_edge_case(char *str)
{
    int i;

    i = 1;
    if (str == NULL)
        return (0);
    if(str[0] == '-')
    {
        while(str[i])
        {
            if(str[i] != 'n')
                return (0);
            i++;
        }
    }
    else
        return (0);
    return (1);
}

int    ft_echo(char **str, int index)
{
    int i;
    int flag;

    i = 1;
    flag = 0;
    if(ft_echo_edge_case(str[i]))
    {
        flag = 1;
        while (ft_echo_edge_case(str[i]))
            i++;
    }
    while(str[i])
    {
        if(str[i][0] == '$')
            i++;
        if(!str[i])
            break;
        if(str[i + 1] != NULL)
            printf(" ");
        printf("%s", str[i]);
        i++;
    }
    if(!flag)
        printf("\n");
    return (1);
}