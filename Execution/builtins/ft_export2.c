/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:39:45 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 01:40:48 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_sort_string_tab(char **tab)
{
    int             i;
    int             j;
    char    *tmp;
    i = 0;
    while (tab[i] != 0)
    {
        j = i;
        while (tab[j] != 0)
        {
            if (ft_strcmp(tab[i], tab[j]) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

char    *ft_mystrdup(char *s1,  int flag)
{
    size_t i;
    int j;
    char *str;

    i = 0;
    j = 0;
    if(flag)
    {
        str = malloc(sizeof(char) * strlen(s1) - 1);
        while(i < ft_strlen(s1) - 1)
        {
            if(s1[i] == '\"')
                i++;
            str[j] = s1[i];
            i++;
            j++;
        }
        str[j] = '\0';
        return (str);
    }
    else
    {
        str = malloc(sizeof(char) * strlen(s1) + 1);
        while(s1[i])
        {
            str[i] = s1[i];
            i++;
        }
        str[i] = '\0';
    }
    return (str);
}

void    ft_export_no_args_case(t_exec *exec)
{
    int i;
    int j;
    int flag;

    i = 0;
    ft_sort_string_tab(exec->envp);
    while(exec->envp[i])
    {
    flag = 0;
        j = 0;
        printf("declare -x ");
        while(exec->envp[i][j])
        {
            if(j != 0 && exec->envp[i][j - 1] == '=' && flag == 0)
            {
                printf("\"");
                flag = 1;
            }
            printf("%c", exec->envp[i][j]);
            j++;
        }
        if(ft_contain(exec->envp[i], '='))
            printf("\"");
        printf("\n");
        i++;
    }
}