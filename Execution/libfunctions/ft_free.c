/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:13:55 by rimney            #+#    #+#             */
/*   Updated: 2022/07/05 02:33:22 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
            free(str[i]);
        i++;
    }
        free(str);
}