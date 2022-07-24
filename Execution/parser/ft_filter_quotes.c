/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:51:21 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 17:52:00 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *ft_filter_command_single_quote(char *temp)
{
    int i;
    int count;
    char *str;
    int j;

    i = 0;
    count = 0;
    j = 0;
    if(temp[0] != '\'')
        return(temp);
    while(temp[i] == '\'')
            i++;
    count = i;
    while(temp[count] != '\'')
        count++;
    str = malloc(sizeof(char) * (count - i) + 1);
    while(temp[i] != '\'')
    {
        str[j] = temp[i];
        j++;
        i++;
    }
    str[i] = 0;
    return (str);
}

char    *ft_filter_command_double_quotes(char *temp)
{
    int i;
    int count;
    char *str;
    int j;

    i = 0;
    count = 0;
    j = 0;
    if(temp[0] != '\"')
        return(temp);
    while(temp[i] == '\"')
            i++;
    count = i;
    while(temp[count] != '\"')
        count++;
    str = malloc(sizeof(char) * (count - i) + 1);
    while(temp[i] != '\"')
    {
        str[j] = temp[i];
        j++;
        i++;
    }
    str[i] = 0;
    return (str);
}

void    ft_filter_command_single_quote_2d_array(char **argv)
{
    int i;
    char    *temp;
    i = 0;
    while(argv[i])
    {
        if(argv[i][0] == '\'')
        {
            temp = argv[i];
            argv[i] = ft_filter_command_single_quote(argv[i]);
            free(temp);   
        }
        i++;
    }
}

void    ft_filter_command_double_quotes_2d_array(char **argv)
{
    int i;
    char    *temp;
    i = 0;
    while(argv[i])
    {
        if(argv[i][0] == '\"')
        {
            temp = argv[i];
            argv[i] = ft_filter_command_double_quotes(argv[i]);
            free(temp);   
        }
        i++;
    }
}