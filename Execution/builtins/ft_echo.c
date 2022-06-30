/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/01 00:07:22 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    ft_echo(char **str, int index)
{
    int i;
    int flag;

    i = 1;
    flag = 0;
    while(str[i])
    {
        printf("%s", str[i]);
        if(str[i + 1])
            printf(" ");
        i++;
    }
    if(!flag)
        printf("\n");
    return i;
}