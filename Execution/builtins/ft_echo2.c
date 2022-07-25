/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:33:18 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 01:38:09 by atarchou         ###   ########.fr       */
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
