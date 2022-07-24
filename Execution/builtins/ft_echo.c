/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 18:13:12 by rimney           ###   ########.fr       */
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

void    ft_echo_single_quote(char *str)
{
    size_t i;

    i = 1;
    while(i < ft_strlen(str) - 1)
        printf("%c", str[i++]);
}

void    ft_echo_norm(char **str, int i)
{
    while(str[i])
    {
        if(str[i][0] == '$')
            i++;
        else if(str[i][0] == '\'')
        {
            ft_echo_single_quote(str[i]);
            i++;
        }
        if(!str[i])
            break;
        printf("%s", str[i]);
        if(str[i + 1])
            printf(" ");
        i++;
    }
}


int    ft_echo(char **str, t_exec *exec)
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
    ft_echo_norm(str, i);
    if(!flag)
        printf("\n");
    exec->env.exit_value = 0;
    return (1);
}